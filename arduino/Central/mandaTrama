void mandaTrama(){

  delay(10);
  xbee.send(zbTx);
  xbee.readPacket(1500);
  Serial.println();
  int err = xbee.getResponse().getErrorCode();
  int stat = xbee.getResponse().getApiId();
  if (stat == 0 && err == 0) {
    Serial.println("ERROR");
  } else if (stat == 117) {
     Serial.println("ERRROR");
  } else {
    Serial.println("OK");
  }
}
