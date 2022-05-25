
#include "device_config.h"
#include "teclado.h"
#include "LCD.h"
#include <stdint.h>
#include <math.h>


#define _XTAL_FREQ 8000000
#define Error 13


int  get_Num(char);
char get_Func(char);
void disp_Res(signed int);
void disp_Error(int);


signed int num1,num2;
char oper;


void main(void) {
    OSCCON = 0x74;
    LCD_init();
    key_init();
    while(1){
        key = key_get();        
        send_to_LCD(key);
        num1 = get_Num(key);
        if (num1 != Error){
            key = key_get();
            send_to_LCD(key);
            oper = get_Func(key);
            if (oper != 'e'){
                key = key_get();
                send_to_LCD(key);
                num2 = get_Num(key);
                if (num2 != Error){
                    key = key_get();
                    send_to_LCD(key);
                    if (key == '='){
                        LCD_cmd(LCD_LINE1);
                        switch (oper){
                            case '+': disp_Res(num1+num2); LCD_cmd(Return_Home); break;
                            case '-': disp_Res(num1-num2); LCD_cmd(Return_Home); break;
                            case '*': disp_Res(num1*num2); LCD_cmd(Return_Home); break;
                            case '/': disp_Res(num1/num2); LCD_cmd(Return_Home); break;
                        }
                    } else if (key == 'C'){
                        LCD_cmd(Clear_DISP);
                    } else disp_Error(0);
                }
            }
        }
  }
} 


int get_Num(char ch){
    int num = 0;
    switch(ch){
    case '0': num = 0; break;
    case '1': num = 1; break;
    case '2': num = 2; break;
    case '3': num = 3; break;
    case '4': num = 4; break;
    case '5': num = 5; break;
    case '6': num = 6; break;
    case '7': num = 7; break;
    case '8': num = 8; break;
    case '9': num = 9; break;
    case 'C':
        LCD_cmd(Clear_DISP);
        num = Error;
        break;
    default:
        disp_Error(0);
        num = Error;
        break;      
    }
    return num;
}

char get_Func(char chf){
    if(chf=='C'){
        LCD_cmd(Clear_DISP);
        return 'e';
    }
    if( chf!='+' && chf!='-' && chf!='*' && chf!='/' ){
        disp_Error(1);
        return 'e';
    }
    return chf;
}

void disp_Res(int numb){
    unsigned char UnitDigit  = 0;
    unsigned char TenthDigit = 0; 
    unsigned char HundrethDigit = 0;
    
    if (numb < 0)
    {
        numb = numb *-1;
        write_string_LCD("-");
    }
    
    HundrethDigit = (numb/100);
    numb = numb - HundrethDigit*100;
    TenthDigit = (numb/10);  
    if (HundrethDigit != 0)
        send_to_LCD(HundrethDigit+'0');
    if (TenthDigit != 0)              
        send_to_LCD(TenthDigit+'0'); 
    UnitDigit = numb - TenthDigit*10;
    send_to_LCD(UnitDigit+'0');    
}

void disp_Error(int numb){
    LCD_cmd(Clear_DISP);
    switch(numb){
    case 0:  write_string_LCD("-Wrong Input");    break;
    case 1:  write_string_LCD("-Wrong Function"); break;
    default: write_string_LCD("-Wrong Input");    break;
    }
}