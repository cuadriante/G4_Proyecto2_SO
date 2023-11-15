#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const char ____versions[]
__used __section("__versions") =
	"\x24\x00\x00\x00\x70\xce\x5c\xd3"
	"_raw_spin_unlock_irqrestore\0"
	"\x18\x00\x00\x00\xd7\xa6\x01\xb7"
	"usb_control_msg\0"
	"\x20\x00\x00\x00\xba\xae\x48\xca"
	"usb_serial_generic_open\0"
	"\x10\x00\x00\x00\xba\x0c\x7a\x03"
	"kfree\0\0\0"
	"\x28\x00\x00\x00\xa6\xd0\xf5\xe9"
	"usb_serial_deregister_drivers\0\0\0"
	"\x18\x00\x00\x00\x31\xf4\xf0\xca"
	"kmalloc_caches\0\0"
	"\x18\x00\x00\x00\x59\x4c\x17\xb1"
	"kmalloc_trace\0\0\0"
	"\x18\x00\x00\x00\x9f\x0c\xfb\xce"
	"__mutex_init\0\0\0\0"
	"\x24\x00\x00\x00\x97\x70\x48\x65"
	"__x86_indirect_thunk_rax\0\0\0\0"
	"\x14\x00\x00\x00\x15\x29\xca\x96"
	"_dev_info\0\0\0"
	"\x14\x00\x00\x00\x1a\xd9\x97\x73"
	"_dev_warn\0\0\0"
	"\x20\x00\x00\x00\x1b\xf0\x0e\x69"
	"usb_control_msg_recv\0\0\0\0"
	"\x1c\x00\x00\x00\x46\x35\x45\x31"
	"__dynamic_dev_dbg\0\0\0"
	"\x14\x00\x00\x00\xd8\xe6\x5f\x47"
	"_dev_err\0\0\0\0"
	"\x28\x00\x00\x00\xb3\x1c\xa2\x87"
	"__ubsan_handle_out_of_bounds\0\0\0\0"
	"\x1c\x00\x00\x00\xcb\xf6\xfd\xf0"
	"__stack_chk_fail\0\0\0\0"
	"\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
	"__fentry__\0\0"
	"\x24\x00\x00\x00\x7c\xb2\x83\x63"
	"__x86_indirect_thunk_rdx\0\0\0\0"
	"\x1c\x00\x00\x00\xca\x39\x82\x5b"
	"__x86_return_thunk\0\0"
	"\x24\x00\x00\x00\xb1\x0a\x24\x10"
	"usb_serial_register_drivers\0"
	"\x20\x00\x00\x00\x0b\x05\xdb\x34"
	"_raw_spin_lock_irqsave\0\0"
	"\x14\x00\x00\x00\xf7\xad\xd0\x13"
	"__kfifo_out\0"
	"\x18\x00\x00\x00\xb5\x28\xc2\x17"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "usbserial");

MODULE_ALIAS("usb:v0403p6001d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "055095D9DDE3C0944848486");
