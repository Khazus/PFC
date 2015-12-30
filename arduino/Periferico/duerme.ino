void duerme() {
  
  digitalWrite(DTR,HIGH);
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable(); //lo ponemos para que pueda dormir
  //apagamos todo
  PRR=B11111111;
  power_timer0_disable();
  power_timer1_disable();
  power_timer2_disable();
  power_adc_disable();
  power_twi_disable();
  power_spi_disable();
  //duerme
  sleep_mode();
  //------->despierta
  PRR=B00000000;
  power_all_enable();
  sleep_disable();
  digitalWrite(4,HIGH);
  
  
}
