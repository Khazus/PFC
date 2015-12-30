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
  delay(50);
  xbee.readPacket();
  RxFlat = 0;
  Serial.println(xbee.getResponse().getApiId(),HEX);
  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
    xbee.getResponse().getZBRxResponse(rx);
    RxFlat = 1;
    SendFlat = 1;

  }
  if (SendFlat == 1) {
    if (RxFlat == 0) {
      Serial.println("Paquete Recibido");
      int tam = rx.getDataLength();
      //Serial.println(tam);
      char Trama[tam];
      for (int aux = 0; aux < tam; aux++) {
        Trama[aux] = (char)rx.getData(aux);
      }
      AL = rx.getRemoteAddress64().getLsb();
      Serial.println(AL,HEX);
      AH = rx.getRemoteAddress64().getMsb();
      Serial.println(AH,HEX);
      AE[0]=AH%256;
      AH=AH>> 8;
      AE[1]=AH%256;
      AH=AH>> 8;
      AE[2]=AH%256;
      AH=AH>> 8;
      AE[3]=AH;
      AE[4]=AL%256;
      AL=AL>> 8;
      AE[5]=AL%256;
      AL=AL>> 8;
      AE[6]=AL%256;
      AL=AL>> 8;
      AE[7]=AL;
      for(int i = 0 ; i < 8 ; i++){
        EEPROM.write(i,AE[i]);
      }
      Serial.println();
      SendFlat = 0;
      existe = 1;
      entra=0;
    }
  }
  return existe;
}
