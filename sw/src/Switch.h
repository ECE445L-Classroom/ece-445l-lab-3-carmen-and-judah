// Switch.h

// The header file for the switch interface
// 
// The following switches are used:
// ___: set alarm
// ___: turn off alarm
// ___: change time
//

// -------Function Prototypes--------
#include <stdint.h>
#ifndef _SWITCH_H_
#define _SWITCH_H_

//extern volatile uint8_t hours, mins, secs;  // Global variables for time


// Define system modes for the alarm clock
typedef enum {
    MAIN_MODE = 0,    // Mode to display current time
    SET_TIME_MODE = 1, // Mode to set time
    SET_ALARM_MODE = 2 // Mode to set alarm
} SysMode;

// Initializes GPIO switches
void sw_Init(void);

// Handle switch input based on the current mode
void SwitchInput(void);

// Debounced check if a switch is pressed
int Switch_Press(uint32_t switchMask);

#endif