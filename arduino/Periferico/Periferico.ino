#include <EEPROM.h>
#include <dht11.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <XBee.h>
#include <stdlib.h>


int TAM_MAX = 55;


//Variables a modificar
int minutos = 30;                          //Minutos entre envios
int horas = 1;                             //Horas entre envíos  

XBee xbee = XBee();

dht11 DHT11;

//NO TOCAR
int temperatura = 26;
int humedad = 16;
int luminosidad = 1000;
boolean presencia=true;
int contador = 1;
int stat = 0;
int err = 0;
int errores=0;
int DTR=3;
int tiempo=0;
int cuenta;
uint8_t AE[8];
uint32_t AL = 0x00000000;
uint32_t AH = 0x00000000;
int RxFlat = 0;
int SendFlat = 0;
uint8_t texto[55] ;
int primero = 1;
int zero;
int entra;


//XBeeAddress64 addr64  = XBeeAddress64(0x0013A200, 0x40BAAB13);  //MAC del CORDINATOR
XBeeAddress64 addr64  = XBeeAddress64(AH, AL);
ModemStatusResponse msr = ModemStatusResponse();
ZBTxRequest zbTx = ZBTxRequest(addr64, texto, sizeof(texto));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();
ZBRxResponse rx = ZBRxResponse();



void setup() {
  pinMode(3,OUTPUT);
  //Iniciamos el puerto serie al BR del xBee
  Serial.begin(115200);
  //Inicializamos el xBee.
  xbee.setSerial(Serial);
  //Comando de prueba
  Serial.println("Activo");
  //Esperamos a que se inicialize la comunicación del xBee en su PAN ID.
  delay(5000);
  //Antes de iniciar nada más, leemos los 8 primeros Bytes de la EEPROM donde almacenamos la mac destino
  zero = 0;
  for(int i = 0 ; i < 8 ; i++){
    AE[i]=EEPROM.read(i);
    Serial.println(AE[i]);
    if(AE[i]==255){
      zero++;  
    }
  }
  Serial.println();
  entra=0;
  if(zero==8){
    entra = 1;
  }else{
    AH =AE[3]*16777216+AE[2]*65536+AE[1]*256+AE[0];
    AL =AE[7]*16777216+AE[6]*65536+AE[5]*256+AE[4];
    Serial.print("Las lecturas se enviarán a 0x");
    Serial.print(AH);
    Serial.println(AL);
  }


  //Iniciamos el contador de errores.
  errores=0;
  //Encendemos el temporizador del wdt
  watchDogOn();
  digitalWrite(4,HIGH);
  //Para comprobar errores:
  tiempo= millis();
}

void loop() {
  if(entra{
    if(leeXBee()){
      Serial.println("ya");
    }
  }else{
    WDTCSR=0x00; //desactivo el wdt
    //
    if(contador == cuenta){
      Serial.println(contador);
      delay(1);
      cuenta = contador-25;
    }
    if (contador > 1) {
      WDTCSR=0x71; //activo el wdt
      duerme();
    } else {
      digitalWrite(DTR,LOW);
      digitalWrite(2,HIGH);
      delay(100);
      //Reenvía la ultima trama.
      xbee.send(zbTx);
      delay(30000);
      
      lectura();
      CreaTrama();
  
      
      xbee.send(zbTx);
  
     
      //comprobamos los errores
      xbee.readPacket(1500);
      Serial.println();
      err = xbee.getResponse().getErrorCode();
      stat = xbee.getResponse().getApiId();
      if (stat == 0 && err == 0) {
        Serial.println("ERROR");
        errores++;
      } else if (stat == 117) {
        Serial.println("ERRROR");
        errores++;
      } else {
        Serial.println("OK");
      }
      if(errores>50){
        softReset();
      }
      
      delay(500);
      ///////////////////////////////////////////////
      
      contador = (60 * minutos)/8;             // Minutos
      //contador = horas * 450;                    // Horas
      cuenta = contador-25;
      //La siguiente linea es solo para realizar pruebas.
  
      //contador = 4; //para pruebas solo
  
      //Lo mandamos a dormir
   
      WDTCSR=0x71; //activo el wdt
      duerme();
    }
  }
}
