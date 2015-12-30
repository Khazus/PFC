void lectura(){
  int chk = DHT11.read(2);
  humedad=DHT11.humidity;
  temperatura=DHT11.temperature;
  presencia = 0;
  if(digitalRead(4)){
    presencia = 5;
  }
  luminosidad=analogRead(A0);
}
