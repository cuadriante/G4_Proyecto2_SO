#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Valores para la pantalla
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Declaramos las variables de los servos
Servo servoMotorPunto;
Servo servoMotorRaya;
Servo servoMotorEspacio;
Servo servoMotorSalto;

// Declaramos las entradas de los botones
int const salto = 6;
int const espacio = 7;
int const raya = 8;
int const punto = 9;

// Declaramos estados de los botones
int estadoPunto;
int estadoRaya;
int estadoEspacio;
int estadoSalto;

// Declaramos pines buzzer y led
int const buzzer = 10;
int const led = 11;

// Declaramos tiempos de espera
int const tiempoDePunto = 500;
int const tiempoDeRaya = tiempoDePunto/2;

// Declaramos string para la pantalla y para la entrada
String textoPantalla;
String textoSerial;

// Función para mover el servo que representa un punto en el código Morse
void moverPunto(){
  servoMotorPunto.write(0);
  delay(tiempoDePunto);
  digitalWrite(buzzer, HIGH);
  servoMotorPunto.write(110);
  delay(tiempoDePunto);
  digitalWrite(buzzer, LOW);
  detectarBoton();
  servoMotorPunto.write(0);
}

// Función para mover el servo que representa una raya en el código Morse
void moverRaya(){
  servoMotorRaya.write(0);
  delay(tiempoDeRaya);
  digitalWrite(buzzer, HIGH);
  servoMotorRaya.write(105);
  delay(tiempoDeRaya * 4);
  digitalWrite(buzzer, LOW);
  detectarBoton();
  servoMotorRaya.write(0);
}

// Función para mover el servo que representa un espacio en el código Morse
void moverEspacio(){
  servoMotorEspacio.write(0);
  delay(tiempoDePunto);
  digitalWrite(buzzer, HIGH);
  servoMotorEspacio.write(120);
  delay(tiempoDePunto);
  digitalWrite(buzzer, LOW);
  detectarBoton();
  servoMotorEspacio.write(0);
}

// Función para mover el servo que representa un salto en el código Morse
void moverSalto(){
  servoMotorSalto.write(0);
  delay(tiempoDePunto);
  digitalWrite(buzzer, HIGH);
  servoMotorSalto.write(110);
  delay(tiempoDePunto);
  digitalWrite(buzzer, LOW);
  detectarBoton();
  servoMotorSalto.write(0);
}

// Función para detectar el estado de los botones y actualizar el texto en pantalla
void detectarBoton(){

  estadoPunto = digitalRead(punto);
  estadoRaya = digitalRead(raya);
  estadoEspacio = digitalRead(espacio);
  estadoSalto = digitalRead(salto);

  if (estadoPunto == HIGH) {
    textoPantalla += ".";
  }
  if (estadoRaya == HIGH) {
    textoPantalla += "-";
  }
  if (estadoEspacio == HIGH) {
    textoPantalla += " ";
  }
  if (estadoSalto == HIGH) {
    textoPantalla += "\n";
  }

}

// Configuración inicial                                                 
void setup() {
  // Iniciamos el monitor serie
  Serial.begin(9600);

  // Iniciamos los server con los puertos
  servoMotorPunto.attach(2);
  servoMotorRaya.attach(3);
  servoMotorEspacio.attach(4);
  servoMotorSalto.attach(5);

  // Iniciarmos los pines de los botones
  pinMode(punto, INPUT);
  pinMode(raya, INPUT);
  pinMode(espacio, INPUT);
  pinMode(punto, INPUT);

  // Iniciamos pines para buzzer y led
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Ponemos los servos en la posición inicial
  servoMotorPunto.write(0);
  delay(tiempoDePunto);
  servoMotorRaya.write(0);
  delay(tiempoDePunto);
  servoMotorEspacio.write(0);
  delay(tiempoDePunto);
  servoMotorSalto.write(0);
  delay(tiempoDePunto);

  // Inicializamos los strings
  textoPantalla = "";
  textoSerial = "";

  // Inicialización del display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println("Proyecto SO");
  display.setTextSize(1);             // Draw 2X-scale text
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println("Codigo Morse \nJason Leiton");
  display.display();
  delay(3000);


}

// Función principal que se ejecuta en bucle
void loop() {

  if (Serial.available() > 0) {
    // Leer el próximo carácter
    char caracterRecibido = Serial.read();

    // Imprimir el carácter en el monitor serie
    Serial.print("Caracter recibido: ");
    Serial.println(caracterRecibido);

    // Logica
    if (caracterRecibido == '.') { //PUNTO
      moverPunto();
    } else if (caracterRecibido == '-') {//PUNTO
      moverRaya();
    } else if (caracterRecibido == 'e') { //ESPACIO
      moverEspacio();
    } else if (caracterRecibido == 's') { //SALTO DE LINEA
      moverSalto();
    } else if (caracterRecibido == 'i') { //INICAR CICLO
      digitalWrite(led, LOW);
      textoPantalla = "";
      textoSerial = "";
    } else if (caracterRecibido == 'f') { //TERMINAR CICLO
      digitalWrite(led, HIGH);
    }

    display.clearDisplay();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println("Puntos y Rayas");
    display.setTextSize(1);  
    display.println(textoPantalla); 
    display.display();
    delay(1000); 

    delay(tiempoDePunto * 2);

    // Agregar el carácter al final del string textoSerial
    textoSerial += caracterRecibido;

    // Escribir al serial
    Serial.write(caracterRecibido);
  }

  // // Recorrer el string textoSerial
  // for (int i = 0; i < textoSerial.length(); i++) {
  //   char caracterActual = textoSerial[i];

  //   delay(tiempoDePunto);

  //   if (caracterActual == '.') {
  //     moverPunto();
  //   } else if (caracterActual == '-') {
  //     moverRaya();
  //   } else if (caracterActual == 'a') {
  //     moverEspacio();
  //   } else if (caracterActual == 'b') {
  //     moverSalto();
  //   }

  //   display.clearDisplay();
  //   display.setTextSize(1);             // Normal 1:1 pixel scale
  //   display.setTextColor(SSD1306_WHITE);        // Draw white text
  //   display.setCursor(0,0);             // Start at top-left corner
  //   display.println("Puntos y Rayas");
  //   display.setTextSize(1);  
  //   display.println(textoPantalla); 
  //   display.display();
  //   delay(1000); 

  //   delay(tiempoDePunto * 2);

  // }

  // digitalWrite(led, HIGH);
  
}