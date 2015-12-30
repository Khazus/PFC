/**************************************************************************************
* La funcion SOS() mandará una señal de socorro óptica en morse, correspondiente a    *
* ...---...                                                                           *
**************************************************************************************/

void SOS(){
  for(int i = 0 ; i < 3 ; i++){
    digitalWrite(13,HIGH);
    delay(300);
    digitalWrite(13,LOW);
    delay(300);
  }  
  for(int i = 0 ; i < 3 ; i++){
    digitalWrite(13,HIGH);
    delay(600);
    digitalWrite(13,LOW);
    delay(300);
  }  
  for(int i = 0 ; i < 3 ; i++){
    digitalWrite(13,HIGH);
    delay(300);
    digitalWrite(13,LOW);
    delay(300);
  }
  delay(1000);
}
