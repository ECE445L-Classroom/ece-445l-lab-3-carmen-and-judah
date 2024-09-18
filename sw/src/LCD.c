// LCD.c

// The LCD interface
// Written by: Carmen Martinez and Judah Thurman
// 
// Connections for the LCD:
// 1  GND			GND
// 2  Vcc			3.3V
// 3  Reset		PA7
// 4  D/C			PA6
// 5  CARD_CS	PB0
// 6  TFT_CS	PA3
// 7  MOSI		PA5
// 8  SCLK		PA2
// 9  MISO		PA4
// 10 Light		3.3V

// x = columns (127 to 0)  along top edge
// y = rows (0 to 159)		 along right edge

// clock bottom left (5,150)
// clock dimensions: 80x80

#include "LCD.h"
#include "Switch.h"
#include "Timer.h"


void DrawClock(){
	
	//Main Menu
	ST7735_DrawBitmap(5,150,clock,80,80);
	
		//analog clock
	ST7735_DrawString(0,0,"Main Menu", ST7735_Color565(0,255,0));
	ST7735_DrawString(0,1,"SW1: Set Time", ST7735_Color565(255,255,255));
	ST7735_DrawString(0,2,"SW2: Set Alarm", ST7735_Color565(255,255,255));
	ST7735_DrawString(0,3,"SW3: Alarm On/Off", ST7735_Color565(255,255,255));
	ST7735_DrawString(0,4,"SW4: Display Mode", ST7735_Color565(255,255,255));
	
		//digital clock - normal
//	uint32_t thours = 12;
//	uint32_t tminutes = 15;
//	uint32_t tseconds = 23;
//	

	
		//digital clock - military
}


void updateAnalogClock(void){
	//erase previous lines
	
	//draw new lines
	
}


void updateDigital1Clock(void){
	ST7735_SetCursor(6,10);
	ST7735_OutUDec(hours);
	ST7735_OutChar(':');
	ST7735_OutUDec(minutes);
	ST7735_OutChar(':');
	ST7735_OutUDec(seconds);
	ST7735_OutString(" PM");
}	


void updateDigital2Clock(void){
	ST7735_SetCursor(6,10);
	ST7735_OutUDec(mhours);
	ST7735_OutChar(':');
	ST7735_OutUDec(minutes);
	ST7735_OutChar(':');
	ST7735_OutUDec(seconds);
	ST7735_OutString(" PM");
}
