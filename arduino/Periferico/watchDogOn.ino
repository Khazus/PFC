void watchDogOn(){
    // Borra la marca de reinicio, el bit WDRF (bit 3) de MCUSR
    MCUSR = MCUSR & B11110111;
    /*  
    Coloca el bit WDCE (bit 4) y el bit WDE bit (bit 3) 
    de WDTCSR. El bit WDCE debe ser colocado en orden a 
    a cambiar WDE o los preescaladores del watchdog. Configurando el 
    bit WDCE permitirá actualizar a los preescaladores y 
    WDE para 4 ciclos de reloj, luego será reiniciado por hardware. 
    */
    WDTCSR = WDTCSR | B00011000; 
    // Establce el preescalador de tiempo de espera de vigilancia a un valor de 1024k
    // el cual rentabilizará el intervalo de tiempo de espera sobre los 8seg.
    WDTCSR = B00100001;
    // Activa la interrupción por temporizador.
    WDTCSR = WDTCSR | B01000000;
    MCUSR = MCUSR & B11110111;
}
