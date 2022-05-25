#include "teclado.h"
#include "device_config.h"
#define _XTAL_FREQ 8000000

void key_init ()
{
    ANSELB = 0;
    TRISB = 0x0F;
    WPUB = 0x0F;
    INTCON2bits.RBPU = 0;
}

char key_scanner (){
    LATB = 0x70;
    switch (PORTB){
        case 0x7E: return '='; break;
        case 0x7D: return '0'; break;
        case 0x7B: return 'C';break;
        case 0x77: return '/'; break;
    }
    
    LATB = 0xB0;
    switch (PORTB){
        case 0xBE: return '7'; break;
        case 0xBD: return '8'; break;
        case 0xBB: return '9'; break;
        case 0xB7: return '*'; break;
    }
    LATB = 0xD0;
    switch (PORTB){
        case 0xDE: return '4'; break;
        case 0xDD: return '5'; break;
        case 0xDB: return '6'; break;
        case 0xD7: return '-'; break;
    }
    LATB = 0xE0;
    switch (PORTB){
        case 0xEE: return '1'; break;
        case 0xED: return '2'; break;
        case 0xEB: return '3'; break;
        case 0xE7: return '+'; break;
    }
    return 'x';
    LATB = 0x00;
   
}

char key_get ()
{
    key = 'x';
    
    while (key == 'x')
    {
        key = key_scanner();
        __delay_ms(200);
    }
    return key;
}
