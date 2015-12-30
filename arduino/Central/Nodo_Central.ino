/******************************************************************

  Red de sensores para monitorización inteligente de vivienda.
  
  Proyecto fin de carrera
  Ingeniero de Telecomunicación, Plan del 98
  Universidad de Sevilla
  
  Alumno: Javier Arcenegui Almenara
  Tutor: Antonio Luque Estepa
  
  Nodo central:
  El nodo central es el encargado en primer lugar de comunicar
  la red de sensores con la nube. En segunda instancia se encarga
  del sistema de alarma. Si estando el sistema de alarma activo
  se detecta una persona sin autentificacion RFID, la alarma
  sonará e informará al inquilino/propietario. En último lugar,
  al igual que el resto de nodos, se encargara tambien de las
  mediciones de Luz, Humedad, Temperatura y Presencia.

  El nodo consta:
  Arduino Uno
  Shield WiFi
  Shield xBee
  Módulo xBee Serie 2 (ZigBee)
  Módulo RFID-RC522
  Sensor PIR
  Sensor DHT11
  LDR  
  
******************************************************************/
/* Nota de versiones */
/* 
  Version 1: Conexión WiFi
  Basicamente lo que vamos a hacer ahora es solo conectarnos a una red WiFi.
  Version 2: Lectura xBee
  Vamos a realizar la lectura de los mensajes entrantes por xBee.
  Version 3: Mandar datos a webService
  Version 4: Leemos la MAC del dispositivo origen de la trama y la mandamos.
*/

//Librerías incorporadas de arduino
#include <WiFi.h>
#include <SPI.h>

//librerias del microcontrolador/compilador
#include <stdlib.h>

//librerias externas
#include <XBee.h>

//Variables necesarias para WiFi:
//Malaga
//Datos de conexion
//char ssid[] = "ONO2475";                        //SSID de la red a la que queremos conectar.
//char pass[] = "7FB4aXJEQUZn";                   //Password de la red. Como es WPA2 no necesitamos mas datos
//Telefono
char ssid[] = "Arduino";                        //SSID de la red a la que queremos conectar.
char pass[] = "30wololo"; 
char tramaGet[100];
char MAC[10];
//variable de estado:
int status = WL_IDLE_STATUS;
//Datos del servidor donde vamos a almecenar los datos que vallamos a subir:
char server[] = "www.ardugeek.es";
//Inicializamos la variable de cliente WiFi.
WiFiClient client;
WiFiClass clase;
uint8_t * MACWIFI;

//Variables necesarias para la lectura del xBee
//todo: poner el tamaño de trama xBee maximo.
char Trama[55];                              //Creamos una trama vacía de 55 caracteres
uint8_t tam=0;                                 //Nos dirá el tamaño de la trama recibida
int RxFlat=0;
int SendFlat=0;
uint32_t macLsb=0;
//Inicalizamos la variable de xBee.
uint8_t texto[1] = {'\0'};
XBee xbee = XBee();
//Declaramos la variable de respuesta del XBee
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();
//Variable de estado del xBee
ModemStatusResponse msr = ModemStatusResponse();
XBeeAddress64 addr64  = XBeeAddress64(0x00000000, 0x0000FFFF);
ZBTxRequest zbTx = ZBTxRequest(addr64, texto, sizeof(texto));


void setup() {
  //inicializamos los pines que vayamos a utilizar.
  pinMode(13,OUTPUT); 
  pinMode(12,INPUT); 
  //Inicializamos el puerto Serie a 115200 ya que es el BaudRate configurado con los xBee.
  Serial.begin(115200);
  //llamamos a la funcion conectarRed.
  conectarRed();
  //Inicializamos el xBee
  xbee.begin(Serial);
}

void loop() {
  if(!digitalRead(12)){
      mandaTrama();
    }
  if(leeXBee()){
    Serial.println("Paquete Recibido:");
    Serial.println(Trama);
    montaTrama();
    Serial.println(tramaGet);
    httpRequest();
    Serial.println("ok");
  }
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
  while( status != WL_CONNECTED ){
    // Serial.print/println solo activo para debugear el programa
    Serial.println("Reiniciando conexion a la red");
    //Realizamos la conexion mediante el siguiente comando:
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
}

void httpRequest() {
  // Cerramos la conexion existente si la hubiera.
  // lo que nos dejaría el Socket libre.
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connectando...");
    // send the HTTP PUT request:
    client.println(tramaGet);
    client.println("Host: www.ardugeek.es");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

  }
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}
