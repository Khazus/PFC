/************************************************************************************
* La funcion conectarRed(); nos permite conectarnos a una red WiFi con los datos    *
* introducidos en las variables ssid[] y pass[]. No requiere ningun atributo y será *
* de tipo void. Por lo que no será necesario la devolución de ningún dato.          *
************************************************************************************/
void conectarRed(){
  //Comprobamos si la Shield WiFi está instalada en el arduino.
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Shield WiFi no instalada en el arduino, instalela y resetee la placa");
    // nos quedaremos en bucle hasta instalar, mandamos SOS desde el led 13
    while (true){
      SOS(); //otras funciones linea: 6
    }
  }
  //Una vez comprobado que tenemos la placa instalada, realizamos la conexión
  while( status != WL_CONNECTED ){
    // Serial.print/println solo activo para debugear el programa
    Serial.println("Iniciando conexion a la red");
    //Realizamos la conexion mediante el siguiente comando:
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  //esto quitar todo.
  Serial.println("El dispositivo esta conectado");
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Potencia de Senal (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}
