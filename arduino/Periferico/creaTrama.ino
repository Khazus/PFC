void CreaTrama() {
  //definimos las variables que vamos a utilizar y las inicializamos
  int trama = 0;
  int auxtrama = 0;
  uint8_t tam;
  uint8_t ASCII = B10000000;
  char datos[4] = {0, 0, 0, 0};
  char pir[]="PIR";
  char tem[]="TEM";
  char hum[]="HUM";
  char luz[]="LUZ";
  
  uint8_t i = 0;
  uint8_t j = 0;
  
  //borrado de trama.
  
  for (i = 0; i < TAM_MAX; i++) {
    texto[i] = 0x00;
  }


  for(i=0;i<3;i++,j++){
    texto[j] = tem[i];
  }
  texto[j++] = '=';
  
  trama = temperatura;
  if (trama >= 1000) {
    texto[j] = 0x30;
    while (trama >= 1000) {
      texto[j] += 1;
      trama -= 1000;
    }
    j++;
    auxtrama = 1;
  }
  if (trama >= 100 || auxtrama == 1) {
    texto[j] = 0x30;
    while (trama >= 100) {
      texto[j] += 1;
      trama -= 100;
    }
    j++;
    auxtrama = 1;
  }
  if (trama >= 10 || auxtrama == 1) {
    texto[j] = 0x30;
    while (trama >= 10) {
      texto[j] += 1;
      trama -= 10;
    }
    j++;
    auxtrama = 1;
  }
  texto[j] = 0x30;
  while (trama >= 1) {
    texto[j] += 1;
    trama -= 1;
  }
  j++;
  auxtrama = 0;

   texto[j++] = '&';
  

  for(i=0;i<3;i++,j++){
    texto[j] = hum[i];
  }
  texto[j++] = '=';
  trama = humedad;
  if (trama >= 1000) {
    texto[j] = 0x30;
    while (trama >= 1000) {
      texto[j] += 1;
      trama -= 1000;
    }
    j++;
    auxtrama = 1;
  }
  if (trama >= 100 || auxtrama == 1) {
    texto[j] = 0x30;
    while (trama >= 100) {
      texto[j] += 1;
      trama -= 100;
    }
    j++;
    auxtrama = 1;
  }
  if (trama >= 10 || auxtrama == 1) {
    texto[j] = 0x30;
    while (trama >= 10) {
      texto[j] += 1;
      trama -= 10;
    }
    j++;
    auxtrama = 1;
  }
  texto[j] = 0x30;
  while (trama >= 1) {
    texto[j] += 1;
    trama -= 1;
  }
  j++;
  auxtrama = 0;

   texto[j++] = '&';
  

  for(i=0;i<3;i++,j++){
    texto[j] = luz[i];
  }
  texto[j++] = '=';

  trama = luminosidad;
  if (trama >= 1000) {
    texto[j] = 0x30;
    while (trama >= 1000) {
      texto[j] += 1;
      trama -= 1000;
    }
    j++;
    auxtrama = 1;
  }
  if (trama >= 100 || auxtrama == 1) {
    texto[j] = 0x30;
    while (trama >= 100) {
      texto[j] += 1;
      trama -= 100;
    }
    j++;
    auxtrama = 1;
  }
  if (trama >= 10 || auxtrama == 1) {
    texto[j] = 0x30;
    while (trama >= 10) {
      texto[j] += 1;
      trama -= 10;
    }
    j++;
    auxtrama = 1;
  }
  texto[j] = 0x30;
  while (trama >= 1) {
    texto[j] += 1;
    trama -= 1;
  }
  j++;
  auxtrama = 0;

  texto[j++] = '&';
  

  for(i=0;i<3;i++,j++){
    texto[j] = pir[i];
  }
  texto[j++] = '=';
  
  if(presencia)
    texto[j++]='1';
  else
    texto[j++]='2';

  texto[j] = 0x00;

}
