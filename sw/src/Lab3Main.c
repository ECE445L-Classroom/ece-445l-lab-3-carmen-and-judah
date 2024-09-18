// Lab3Main.c
// Runs on LM4F120/TM4C123
// Uses ST7735.c to display the clock
// patterns to the LCD.
//    16-bit color, 128 wide by 160 high LCD
// Mark McDermott, Daniel Valvano and Jonathan Valvano
// Lab solution, do not post
// August 3,2024

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2024

 Copyright 2024 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// Specify your hardware connections, feel free to change
// PD0 is squarewave output to speaker
// PE0 is mode select
// PE1 is left
// PE2 is right 
// PE3 is up
// PE4 is down
// if alarm is sounding, any button will quiet the alarm

#include <stdio.h>
#include <stdint.h>
#include "../inc/ST7735.h"
#include "../inc/PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "Lab3.h"
#include "Switch.h"
#include "Timer.h"
#include "LCD.h"
#include "Speaker.h"


// ---------- Definitions --------------------
#define PF0	(*((volatile uint32_t *)0x40025004))		// SW1 (0x0004)
#define PF1	(*((volatile uint32_t *)0x40025008))		// SW2 (0x0008)
#define PF2	(*((volatile uint32_t *)0x40025010))		// SW3 (0x0010)
#define PF3	(*((volatile uint32_t *)0x40025020))		// SW4 (0x0020)
								// LED for debugging


// ---------- Prototypes   -------------------
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode

//initialize current time
uint8_t hours = 1;
uint8_t mhours = 13;
uint8_t minutes = 25;
uint8_t seconds = 12;

//initialize displayMode and mode
uint8_t displayMode = 0; 		//analog
uint8_t menu = 0; 					//main



// ---------- Main --------------------------
int main(void){
  DisableInterrupts();
  PLL_Init(Bus80MHz);    						// bus clock at 80 MHz
	Timer0A_Init(1);									// Initialize Timer0A with priority 1
	Speaker_Init();
	ST7735_InitR(INITR_REDTAB);				// initialize LCD
	
	
	DrawClock();
	
  EnableInterrupts();
  while(1){
		SwitchInput();
  }
}

