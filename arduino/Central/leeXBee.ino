/***********************************************************************************
* Se ejecuta la funcion lee xBee para leer, en el caso de que halla alguna trama   *
* Devuelve como resultado el tamaño de la trama. Quedandose almacenada la trama en *
* la variable vacía Trama                                                          *
***********************************************************************************/
/****
Problemas entre versiones, resulta que al cambiar
****/
int leeXBee() {
  //Leemos el Paquete
  int existe = 0;
  xbee.readPacket();
  RxFlat = 0;
  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
    xbee.getResponse().getZBRxResponse(rx);
    RxFlat = 1;
    SendFlat = 1;

  }
  if (SendFlat == 1) {
    if (RxFlat == 0) {
      Serial.println("Paquete Recibido");
      tam = rx.getDataLength();
      //Serial.println(tam);
      for (int aux = 0; aux < 55; aux++) {
        Trama[aux] = (char)rx.getData(aux);
      }
      macLsb = rx.getRemoteAddress64().getLsb();
      Serial.println(macLsb);
      for (int aux = 0; aux < 10; aux++) {
        MAC[aux] = 0x00;
      }
      int auxi = 0;
      while (macLsb >= 1000000000) {
        auxi++;
        macLsb -= 1000000000;
      }
      Serial.print(auxi);
      MAC[9] = auxi;
      auxi = 0;
      while (macLsb >= 100000000) {
        auxi++;
        macLsb -= 100000000;
      }
      Serial.print(auxi);
      MAC[8] = auxi;
      auxi = 0;
      while (macLsb >= 10000000) {
        auxi++;
        macLsb -= 10000000;
      }
      Serial.print(auxi);
      MAC[7] = auxi;
      auxi = 0;
      while (macLsb >= 1000000) {
        auxi++;
        macLsb -= 1000000;
      }
      Serial.print(auxi);
      MAC[6] = auxi;
      auxi = 0;
      while (macLsb >= 100000) {
        auxi++;
        macLsb -= 100000;
      }
      Serial.print(auxi);
      MAC[5] = auxi;
      auxi = 0;
      while (macLsb >= 10000) {
        auxi++;
        macLsb -= 10000;
      }
      Serial.print(auxi);
      MAC[4] = auxi;
      auxi = 0;
      while (macLsb >= 1000) {
        auxi++;
        macLsb -= 1000;
      }
      Serial.print(auxi);
      MAC[3] = auxi;
      auxi = 0;
      while (macLsb >= 100) {
        auxi++;
        macLsb -= 100;
      }
      Serial.print(auxi);
      MAC[2] = auxi;
      auxi = 0;
      while (macLsb >= 10) {
        auxi++;
        macLsb -= 10;
      }
      Serial.print(auxi);
      MAC[1] = auxi;
      auxi = 0;
      while (macLsb >= 1) {
        auxi++;
        macLsb -= 1;
      }
      Serial.print(auxi);
      MAC[0] = auxi;
      auxi = 0;

      /* MAC[9] = (macLsb/1000000000);
       macLsb = macLsb - MAC[9]*1000000000;
       MAC[8] = (macLsb/100000000);
       macLsb = macLsb - MAC[8]*100000000;
       MAC[7] = (macLsb/10000000);
       macLsb = macLsb - MAC[7]*10000000;
       MAC[6] = (macLsb/1000000);
       macLsb = macLsb - MAC[6]*1000000;
       MAC[5] = (macLsb/100000);
       macLsb = macLsb - MAC[5]*100000;
       MAC[4] = (macLsb/10000);
       macLsb = macLsb - MAC[4]*10000;
       MAC[3] = (macLsb/1000);
       macLsb = macLsb - MAC[3]*1000;
       MAC[2] = (macLsb/100);
       macLsb = macLsb - MAC[2]*100;
       MAC[1] = (macLsb/10);
       macLsb = macLsb - MAC[1]*10;
       MAC[0] = (macLsb);*/
      Serial.write(MAC);

      Serial.println();
      SendFlat = 0;
      existe = 1;
    }
  }
  return existe;
}



/****original
void leeXBee() {
  //Leemos el Paquete
  xbee.readPacket();
  RxFlat=0;
  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
    xbee.getResponse().getZBRxResponse(rx);
    RxFlat=1;
    SendFlat=1;

  }
  if (SendFlat==1){
    if(RxFlat==0){
      Serial.println("Paquete Recibido");
      tam=rx.getDataLength();
      Serial.println(tam);
      for(int aux=0;aux<150;aux++){
        Trama[aux]=(char)rx.getData(aux);
      }
      SendFlat=0;
      Serial.println(Trama);

    }
  }
}
/*/
