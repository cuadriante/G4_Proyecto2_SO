#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/tty.h>
#include <linux/tty_driver.h>
#include <linux/tty_flip.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>
#include <linux/usb.h>
#include <linux/serial.h>
#include <linux/gpio/driver.h>
#include <linux/usb/serial.h>
#include "test_driver.h"
#include "test_driver_ID.h"

struct ftdi_private {
	enum ftdi_chip_type chip_type; /* type of device, either SIO or FT8U232AM */
	int baud_base;		/* baud base clock for divisor setting */
	int custom_divisor;	/* custom_divisor kludge, this is for baud_base (different from what goes to the chip!) */
	u16 last_set_data_value; /* the last data state set - needed for doing a break*/
	int flags;		/* some ASYNC_xxxx flags are supported */
	unsigned long last_dtr_rts;	/* saved modem control outputs */
	char prev_status;        /* Used for TIOCMIWAIT */
	char transmit_empty;	/* If transmitter is empty or not */
	u16 interface;		/* FT2232C, FT2232H or FT4232H port interface (0 for FT232/245) */
	speed_t force_baud;	/* if non-zero, force the baud rate tothis value */
	int force_rtscts;	/* if non-zero, force RTS-CTS to alwaysbe enabled */

	unsigned int latency;		/* latency setting in use */
	unsigned short max_packet_size;
	struct mutex cfg_lock; /* Avoid mess by parallel calls of config ioctl() and change_speed() */

#ifdef CONFIG_GPIOLIB
	struct gpio_chip gc;
	struct mutex gpio_lock;	/* protects GPIO state */
	bool gpio_registered;	/* is the gpiochip in kernel registered */
	bool gpio_used;		    /* true if the user requested a gpio */
	u8 gpio_altfunc;	    /* which pins are in gpio mode */
	u8 gpio_output;		    /* pin directions cache */
	u8 gpio_value;		    /* pin value for outputs */
#endif
};

/* struct ftdi_sio_quirk is used by devices requiring special attention. */
struct ftdi_sio_quirk {
	int (*probe)(struct usb_serial *);
	/* Special settings for probed ports. */
	void (*port_probe)(struct ftdi_private *);
};

static const struct usb_device_id id_table_combined[] = {
	{ USB_DEVICE(FTDI_VID, FTDI_8U232AM_PID) },
	{ }					/* Terminating entry */
};

MODULE_DEVICE_TABLE(usb, id_table_combined);

static const char *ftdi_chip_name[] = {
	[FT232RL] = "FT232RL",
};

/* function prototypes for a FTDI serial converter */
static int  probe(struct usb_serial *serial,const struct usb_device_id *id);
static int  port_probe(struct usb_serial_port *port);
static void port_remove(struct usb_serial_port *port);
static int  open(struct tty_struct *tty, struct usb_serial_port *port);
static int write(struct usb_serial_port *port,void *dest, size_t size);

static struct usb_serial_driver ftdi_sio_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"DriverTest",
	},
	.description =		"USB Seria Test - Aldo",
	.id_table =		id_table_combined,
	.num_ports =		1,
	.probe =		probe,
	.port_probe =		port_probe,
	.port_remove =		port_remove,
	.open =			open,
	.prepare_write_buffer =	write,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&ftdi_sio_device, NULL
};

#define WDR_TIMEOUT 5000 /* default urb timeout */

// Funciones de utilidad
static int write_latency_timer(struct usb_serial_port *port)
{
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	struct usb_device *udev = port->serial->dev;
	int rv;
	int l = priv->latency;
	if (priv->flags & ASYNC_LOW_LATENCY)
		l = 1;

	dev_dbg(&port->dev, "%s: setting latency timer = %i\n", __func__, l);

	rv = usb_control_msg(udev,
			     usb_sndctrlpipe(udev, 0),
			     FTDI_SIO_SET_LATENCY_TIMER_REQUEST,
			     FTDI_SIO_SET_LATENCY_TIMER_REQUEST_TYPE,
			     l, priv->interface,
			     NULL, 0, WDR_TIMEOUT);
	if (rv < 0)
		dev_err(&port->dev, "Unable to write latency timer: %i\n", rv);
	return rv;
}

static int _read_latency_timer(struct usb_serial_port *port)
{
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	struct usb_device *udev = port->serial->dev;
	u8 buf;
	int rv;

	rv = usb_control_msg_recv(udev, 0, FTDI_SIO_GET_LATENCY_TIMER_REQUEST,
				  FTDI_SIO_GET_LATENCY_TIMER_REQUEST_TYPE, 0,
				  priv->interface, &buf, 1, WDR_TIMEOUT,
				  GFP_KERNEL);
	if (rv == 0)
		rv = buf;

	return rv;
}

static int read_latency_timer(struct usb_serial_port *port){
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	int rv;

	rv = _read_latency_timer(port);
	if (rv < 0) {
		dev_err(&port->dev, "Unable to read latency timer: %i\n", rv);
		return rv;
	}

	priv->latency = rv;

	return 0;
}
// Determina el tipo de chip en base a la config del USB
static void ftdi_determine_type(struct usb_serial_port *port){
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	struct usb_serial *serial = port->serial;
	struct usb_device *udev = serial->dev;
	unsigned version;
	unsigned interfaces;
	priv->baud_base = 48000000 / 2;

	version = le16_to_cpu(udev->descriptor.bcdDevice);
	interfaces = udev->actconfig->desc.bNumInterfaces;
	dev_dbg(&port->dev, "%s: bcdDevice = 0x%x, bNumInterfaces = %u\n", __func__,
		version, interfaces);
	if (version < 0x900) {
		/*FT232RL */
		priv->chip_type = FT232RL;
	} 

	dev_info(&udev->dev, "Detected %s\n", ftdi_chip_name[priv->chip_type]);
}

//El tamaño maximo del paquete
static void ftdi_set_max_packet_size(struct usb_serial_port *port){
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	struct usb_interface *interface = port->serial->interface;
	struct usb_endpoint_descriptor *ep_desc;
	unsigned num_endpoints;
	unsigned i;

	num_endpoints = interface->cur_altsetting->desc.bNumEndpoints;
	if (!num_endpoints)
		return;

	for (i = 0; i < num_endpoints; i++) {
		ep_desc = &interface->cur_altsetting->endpoint[i].desc;
		if (!ep_desc->wMaxPacketSize) {
			ep_desc->wMaxPacketSize = cpu_to_le16(0x40);
			dev_warn(&port->dev, "Overriding wMaxPacketSize on endpoint %d\n",
					usb_endpoint_num(ep_desc));
		}
	}
	priv->max_packet_size = usb_endpoint_maxp(ep_desc);
}

static int ftdi_gpio_init(struct usb_serial_port *port){
	return 0;
}

static void ftdi_gpio_remove(struct usb_serial_port *port) { }


// Funciones del file operatior
static int probe(struct usb_serial *serial,const struct usb_device_id *id){
	const struct ftdi_sio_quirk *quirk =(struct ftdi_sio_quirk *)id->driver_info;

	if (quirk && quirk->probe) {
		int ret = quirk->probe(serial);
		if (ret != 0)
			return ret;
	}

	usb_set_serial_data(serial, (void *)id->driver_info);

	return 0;
}

static int port_probe(struct usb_serial_port *port){
	struct ftdi_private *priv;
	const struct ftdi_sio_quirk *quirk = usb_get_serial_data(port->serial);
	int result;

	priv = kzalloc(sizeof(struct ftdi_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mutex_init(&priv->cfg_lock);

	if (quirk && quirk->port_probe)
		quirk->port_probe(priv);

	usb_set_serial_port_data(port, priv);

	ftdi_determine_type(port);
	ftdi_set_max_packet_size(port);
	if (read_latency_timer(port) < 0)
		priv->latency = 16;
	write_latency_timer(port);

	result = ftdi_gpio_init(port);
	if (result < 0) {
		dev_err(&port->serial->interface->dev,"GPIO initialisation failed: %d\n",result);
	}
	return 0;
}

static void port_remove(struct usb_serial_port *port){
	struct ftdi_private *priv = usb_get_serial_port_data(port);

	ftdi_gpio_remove(port);

	kfree(priv);
}

static int open(struct tty_struct *tty, struct usb_serial_port *port){
	struct usb_device *dev = port->serial->dev;
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			FTDI_SIO_RESET_REQUEST, FTDI_SIO_RESET_REQUEST_TYPE,
			FTDI_SIO_RESET_SIO,
			priv->interface, NULL, 0, WDR_TIMEOUT);

	return usb_serial_generic_open(tty, port);
}

static int write(struct usb_serial_port *port,void *dest, size_t size){
	struct ftdi_private *priv;
	int count;
	unsigned long flags;

	priv = usb_get_serial_port_data(port);

	if (priv->chip_type == SIO) {
		unsigned char *buffer = dest;
		int i, len, c;
		count = 0;
		spin_lock_irqsave(&port->lock, flags);
		for (i = 0; i < size - 1; i += priv->max_packet_size) {
			len = min_t(int, size - i, priv->max_packet_size) - 1;
			c = kfifo_out(&port->write_fifo, &buffer[i + 1], len);
			if (!c)
				break;
			port->icount.tx += c;
			buffer[i] = (c << 2) + 1;
			count += c + 1;
		}
		spin_unlock_irqrestore(&port->lock, flags);
	} else {
		count = kfifo_out_locked(&port->write_fifo, dest, size,&port->lock);
		port->icount.tx += count;
	}
	return count;
}
module_usb_serial_driver(serial_drivers, id_table_combined);
MODULE_AUTHOR("adri");
MODULE_DESCRIPTION("USB - Serial Driver SO");
MODULE_LICENSE("GPL");