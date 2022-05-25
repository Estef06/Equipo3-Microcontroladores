#include "device_config.h"
#include "LCD.h"

void medir_frec (void);
int cuentas;

void main (void){
    OSCCON=0b00110100;  //frec OSCILADOR 1MH
    TRISAbits.TRISA4=1;
    LCD_init();
    
    //Escribir la frecuencia en el display
    write_string_LCD("Frecuencia:"); //Escribir la frecuencia en el display
    cursor_position(1,0);
    write_string_LCD("    Hz");
    write_direction('L');
    
    while (1){
        cursor_position(1,2);
        medir_frec();
        desplegar(cuentas);
    }
    
    
}

void medir_frec (void){
    TMR1L=0xEE;    //CONFIG TIMER1  byte low
    TMR1H=0x85;  //byte high
    T1GCONbits.TMR1GE=0;  //Global enabe
    PIR1bits.TMR1IF=0;  //Apagar flag de interrupción
    T1CON=0b00110001;     //ENECENDER TIMER 1
    
    while( PIR1bits.TMR1IF==0){  //Mientras no termine de contar 1 s
        T0CON=0b11111000; //config/encender contador
    }
    cuentas=TMR0L;  //Asigna el valor de las transiciones negativas en la variable cuenta, es decir, la frecuencia en HZ
    T0CON=0;  // Reiniciar Timer 0
    T1CON=0;  // Reiniciar Timer 1
    PIR1bits.TMR1IF=0;//Apagar la bandera
    TMR0L=0; //Reiniciar cuenta
     
}
