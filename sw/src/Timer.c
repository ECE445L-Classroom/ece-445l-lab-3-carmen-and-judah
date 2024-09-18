// Timer.c
// The timer interface
// Written by: Carmen Martinez and Judah Thurman

#include "Timer.h"
#include "LCD.h"


#define NVIC_EN0_INT19          0x00080000  // Interrupt 19 enable



// ***************** Timer0A_Init ****************
// Activate Timer0A interrupts every second
// Inputs:  priority 0 (highest) to 7 (lowest)
// Outputs: none
void Timer0A_Init(uint32_t priority){
  SYSCTL_RCGCTIMER_R |= 0x01;      // 0) activate timer0
	while(SYSCTL_RCGCTIMER_R != 0x01){}
  TIMER0_CTL_R &= ~0x00000001;     // 1) disable timer0A during setup
  TIMER0_CFG_R = 0x00000000;       // 2) configure for 32-bit timer mode
  TIMER0_TAMR_R = 0x00000002;      // 3) configure for periodic mode, default down-count settings
	TIMER0_TAILR_R = 79999999;       // 4) reload value [frequency of interrupt = bus clock/(reload+1)]
  TIMER0_TAPR_R = 0;               // 5) 
  TIMER0_ICR_R = 0x00000001;       // 6) clear timer0A timeout flag
  TIMER0_IMR_R |= 0x00000001;      // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|(priority<<29); 
  NVIC_EN0_R = NVIC_EN0_INT19;     // 9) enable interrupt 19 in NVIC
  TIMER0_CTL_R |= 0x00000001;      // 10) enable timer0A
}


// ***************** Timer0A_Handler ****************
// Timer0A will interrupt every second and update the time variables
// Inputs:  none
// Outputs: none
void Timer0A_Handler(){
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;	// acknowledge timer0A timeout
	
	seconds++;						//update time
	if(seconds > 60){
		seconds = 0;
		minutes++;
		if(minutes > 60){
			minutes = 0;
			hours++;
			mhours++;
			if(hours > 12){		// TODO: check for military time mode
				hours = 1;
			}
			if(mhours > 24){
				mhours = 0;
			}
		}
	}
	
	if(displayMode == 0){
		updateAnalogClock();
	}
	if(displayMode == 1){
		updateDigital1Clock();
	}
	if(displayMode == 2){
		updateDigital2Clock();
	}
}