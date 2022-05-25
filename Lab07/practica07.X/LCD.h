
#define LCDdataWrite LATD
#define LCDdataRead  PORTD
#define LCDdataDir TRISD

#define LCD_RS       LATCbits.LATC2
#define LCD_RS_Dir   TRISCbits.TRISC2
#define LCD_RW       LATCbits.LATC1
#define LCD_RW_Dir   TRISCbits.TRISC1
#define LCD_E        LATCbits.LATC0
#define LCD_E_Dir    TRISCbits.TRISC0


#define setLCD_8bits_2Lines_smallFont  0b00111000
#define setLCD_8bits_2Lines_bigFont    0b00111100

#define  DISPLAY_ALL_ON				0b00001111
#define  DISPLAY_ON_C_OFF_B_OFF		0b00001100
#define  DISPLAY_ON_C_ON_B_OFF      0b00001110
#define  DISPLAY_ON_C_OFF_B_ON      0b00001101

#define	 EMS_INC_S			0b00000110

#define	DISP_MOVE_RIGHT		0b00011100
#define	DISP_MOVE_LEFT		0b00011000
#define	CURSOR_MOVE_RIGHT	0b00010100
#define	CURSOR_MOVE_LEFT	0b00010000

#define LCD_LINE0 0x00
#define LCD_LINE1 0xC0

#define Return_Home 0b00000010
#define Clear_DISP  0b00000001


void LCD_init(void);
void LCD_cmd (char);
void send_to_LCD (char);
void write_string_LCD (const char*);