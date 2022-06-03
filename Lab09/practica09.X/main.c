#include "device_config.h"  

#define _XTAL_FREQ 8000000
#define BUTTON PORTBbits.RB0                            //RB0 boton para crosswalk

enum por_dir {output = 0x00, input = 0xFF};
enum por_ACDC {digital = 0x00, analog = 0xFF}; 

void high_isr (void);       //Función de interrupción 
void init(void);            //Inicialización de puertos y configuración de interrupción 
void delay1S(void);         //Función para configurar un delay con timer
void state1(void);          // Definición del estado 1
void state2(void);          //Definición del estado 2
void state3(void);          //Definición del estado 3
void state4(void);          //Definición del estado 4
void state5(void);          //Definición del estado 5

char cuenta = 0;            //Cuenta de las veces que se ha solicitado habilitar el crosswalk

//Main program donde se establece la secuencia en la que deben de ocurrir los eventos
void main(void){
    init();
    while(1){
        state1();
        state2();
        while (cuenta != 0){
            state3();
            cuenta--;
        }
        state4();
        state5();
    }
}


void init(){
    
    OSCCON = 0b01100100;   
    
    
    RCONbits.IPEN = 1;      
    INTCONbits.GIEH = 1;    
    INTCONbits.GIEL = 1;    
    
    INTCON2bits.INTEDG0 = 0;
    INTCONbits.INT0IE = 1;  
    INTCONbits.INT0IF = 0;  
    
    // Ports Init
    ANSELD = digital;       
    TRISD = output;        
    PORTD = 0;
    ANSELA = digital;     
    TRISA = output;       
    PORTA = 0;
    ANSELB = digital;      
    TRISBbits.TRISB0 = 1;   
}

/* Las siguientes funciones para los estados de los semaforos, asignan los leds que deberan encenderse en cada caso*/
void state1(){
    LATD = 0x14;
    delay1S();
    delay1S();
    delay1S();
}

void state2(){
    LATD = 0x12;
    delay1S();
}

void state3(){
    LATD = 0x99;
    delay1S();
}

void state4(){
    LATD = 0x41;
    delay1S();
    delay1S();
    delay1S();
}

void state5(){
    LATD = 0x21;
    delay1S();
}

void delay1S(){
    TMR0L = 0xEE;
    TMR0H = 0x85;
    T0CON = 0b10000101;     
    while (INTCONbits.TMR0IF == 0); 
    INTCONbits.TMR0IF = 0;  
    T0CON = 0;
}

/*Interrupción de alta prioridad en donde cada vez que el botón se presiona, se incrementa la variable "cuenta" en uno
Además de limitar el valor de la cuenta a 8*/ 
void __interrupt (high_priority) high_isr (void){
    __delay_ms(30);    
    if (BUTTON == 0){
        cuenta++;
        if (cuenta > 8){
            cuenta = 8;
        } 
    }
    INTCONbits.INT0IF = 0;
}

