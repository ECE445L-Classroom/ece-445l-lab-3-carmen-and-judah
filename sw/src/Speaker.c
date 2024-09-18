// Speaker.c

// The Speaker interface
//
// Connections for the speaker:
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Speaker.h"
#include "Timer.h"

#define SPEAKER (*((volatile uint32_t *)0x40025010))
#define SPEAKERMASK 0x03

void Speaker_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x20;  // Enable clock for Port F
  while ((SYSCTL_PRGPIO_R & 0x20) == 0) {};  // Wait until Port F is ready
  
	GPIO_PORTF_DIR_R |= SPEAKER;   // Set PF2 as output
  GPIO_PORTF_DEN_R |= SPEAKER;   // Enable digital function for PF2
	GPIO_PORTA_AFSEL_R &= ~SPEAKERMASK; 
	GPIO_PORTA_AMSEL_R &= ~SPEAKERMASK;
}

// Turn on the speaker (produce sound)
void AlarmSoundOn(void){
  while(1){
    SPEAKER ^= SPEAKERMASK;  // Set PF2 to high
		for(int i = 0; i < 500000; i++){} 
  }
}
// Turn off the speaker (stop sound)
void AlarmSoundOff(void){
  SPEAKER = 0x00; // Set PF2 to low
}
// Timer0A ISR for toggling the speaker pin

