/*************************************************************************
* La funcion montaTrama, genera una trama para poder hacer la llamada al *
* webservice, que introducirá los datos en una base de datos.            *
*************************************************************************/
//GET /pfc/webservice.php?ROOM=COCINA&TEM=27&HUM=56&LUZ=800&PIR=2 HTTP/1.1"
void montaTrama(){
  char cabecera[]="GET /pfc/webservice.php?MAC=";
  char final[]=" HTTP/1.1";
  int i = 0;
  int j = 0;
  
  //Borramos la trama.
  for (i = 0; i < 100; i++) {
    tramaGet[i] = 0x00;
  }
  for(i = 0 ; i < 28 ; i++,j++){
    tramaGet[j] = cabecera[i];
  }
  for(i = 0; i<10; i++ , j++){
    tramaGet[j] = MAC[9-i]+'0';
  }
  tramaGet[j++]='&';
  for(i = 0 ; Trama[i] != 0x00 ; i++,j++){
    tramaGet[j] = Trama[i];
  }
  
  for(i = 0 ; i < 9 ; i++,j++){
    tramaGet[j] = final[i];
  }
}

