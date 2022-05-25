#include "LCD.h"
#include "device_config.h"
#define _XTAL_FREQ 1000000

void LCD_init(){
    LCDdataDir = 0x00;
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_E  = 0;
    LATC = 0;               
    LCD_E_Dir = 0;          
    LCD_RS_Dir = 0;        
    LCD_RW_Dir = 0;        
    LCD_cmd(setLCD_8bits_2Lines_smallFont);
    __delay_ms(250);  
    LCD_cmd(DISPLAY_ON_C_ON_B_OFF);
    __delay_ms(250);  
    LCD_cmd(Clear_DISP);          
    __delay_ms(250); 
}
void LCD_cmd(char cx) {
    LCD_RS = 0;             
    LCD_RW = 0;             
    LCD_E  = 1;             
    Nop();
    LCDdataWrite = cx;      
    Nop();
    LCD_E = 0;             
}
void send_to_LCD(char xy){
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_E  = 1;
    LCDdataWrite = xy;
    Nop();
    Nop();
    LCD_E  = 0;
    __delay_ms(250);
}
void write_string_LCD (const char *s){
    while(*s)
        send_to_LCD(*s++);
}

void desplegar (int numb){
    unsigned char UnitDigit  = 0;
    unsigned char TenthDigit = 0; 
    unsigned char HundrethDigit = 0;
    
    HundrethDigit = (numb/100);
    TenthDigit = ((numb-HundrethDigit*100)/10); 
    UnitDigit = numb -HundrethDigit*100- TenthDigit*10;
    
    if (LCD_dir=='R'){
        send_to_LCD(HundrethDigit+48);
        send_to_LCD(TenthDigit+48);
        send_to_LCD(UnitDigit+48);
    }
    else if (LCD_dir=='L'){
      send_to_LCD(UnitDigit+48); 
      send_to_LCD(TenthDigit+48);
      send_to_LCD(HundrethDigit+48);
    }
}

void cursor_position(char fila, char col)
{
    unsigned char position = 0;
    
    switch (fila)
    {
        case 0: {
            position = 0x80|col;
            LCD_cmd(position);
        }
        case 1: {
            position = 0xC0|col;
            LCD_cmd(position);
        }
        
        default: Nop();
        break;
    }
}
void write_direction(char direction){
    if (direction=='R'){   //De izq a derecha
        LCD_cmd(EMS_INC_S); //Incremental    
        LCD_dir= 'R';
    }
    else if (direction=='L'){
        LCD_cmd(EMS_DEC_S);
         LCD_dir= 'L';
    }
}