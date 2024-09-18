// Switch.c
//
// The Switch interface
// 
// The following switches are used:
// PF0: set alarm 
// PF1: turn off alarm 
// PF2: change time 
// PF3: Display

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "switch.h"
#include "timer.h"
#define debounce 10 

// Switch Pins (PF0, PF1, PF3, PF4)
#define SWITCH_MODE 0x01  // PF0: Mode switch (Main Mode, Set Time Mode, Set Alarm Mode)
#define SWITCH_HOURS 0x10 // PF4: Increment hours
#define SWITCH_MINS 0x04  // PF3: Increment minutes (reuses mode switch)
#define SWITCH_SECS 0x02  // PF1: Increment seconds

//extern volatile uint8_t hours, mins, secs;  // Global variables for time
extern volatile uint8_t alarmHours, alarmMinutes;  // Global variables for alarm time
extern volatile SysMode curMode;  // Externally defined mode

void Sw_Init(void){volatile unsigned long delay;
		SYSCTL_RCGCGPIO_R |= 0x20;  // Enable clock for Port F
    while ((SYSCTL_PRGPIO_R & 0x20) == 0) {};  // Wait until Port F is ready
    
    // Unlock PF0 (which is locked by default)
    GPIO_PORTF_LOCK_R = 0x4C4F434B;  
    GPIO_PORTF_CR_R |= SWITCH_MODE;  // Commit the change to PF0

    // Configure PF0, PF1, PF4 as inputs
    GPIO_PORTF_DIR_R &= ~(SWITCH_MODE | SWITCH_SECS | SWITCH_MINS |SWITCH_HOURS);

    // Enable digital function on PF0, PF1, PF4
    GPIO_PORTF_DEN_R |= (SWITCH_MODE | SWITCH_SECS | SWITCH_MINS | SWITCH_HOURS);
}
//chech if switch is pressed
int Switch_Press(uint32_t switchMask){
	if(!(GPIO_PORTF_DATA_R & switchMask)){ // if the switch is pressed
		SysTick_Wait10ms(debounce);
		if(!(GPIO_PORTF_DATA_R&switchMask)){
			return 1;
		}
	}return 0;
}

void SwitchInput(void){
	uint32_t hours, mins, secs;
	if (Switch_Press(SWITCH_MODE)) {
        curMode = (curMode + 1) % 3;  // Cycle between MAIN_MODE, SET_TIME_MODE, SET_ALARM_MODE
        while (!(GPIO_PORTF_DATA_R & SWITCH_MODE));  // Simple debounce: wait for release
    }
	if(curMode == SET_TIME_MODE){
		if(Switch_Press(SWITCH_HOURS)){
			hours = (hours + 1) % 24; // Increment hours, wrap around after 23
		}
		if(Switch_Press(SWITCH_MINS)){
			mins = (mins + 1) % 60; // Increment minutes, wrap around after 59
		}
		if(Switch_Press(SWITCH_SECS)){
			secs = (secs + 1) % 60; // Increment seconds, wrap around after 59
		}
	}
	if(curMode == SET_ALARM_MODE){
		if(Switch_Press(SWITCH_HOURS)){
			hours = (hours + 1) % 24; // Increment hours, wrap around after 23
		}
		if(Switch_Press(SWITCH_HOURS)){
			mins = (mins + 1) % 60; // Increment minutes, wrap around after 59
		}
	}
}