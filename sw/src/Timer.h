// Timer.h

// The header file for the timer interface
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// ******Prototypes******
void Timer0A_Init(uint32_t priority);
void Timer0A_Handler(void);

// ******Variables*******
extern uint8_t hours, minutes, seconds;
extern uint8_t mhours;
extern uint8_t alarm_h, alarm_m;

extern uint8_t displayMode;	//0 = analog, 1 = digital norm, 2 = digital military
extern uint8_t menu; //0 = main, 1 = set time, 2 = set alarm