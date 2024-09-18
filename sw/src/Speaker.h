// Speaker.h

// The header file for the speaker interface
//
// Connections for the speaker:
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#ifndef _SPEAKER_H_
#define _SPEAKER_H_

// Initialize the speaker system
void Speaker_Init(void);

// Turn the alarm sound on
void AlarmSoundOn(void);

// Turn the alarm sound off
void AlarmSoundOff(void);


#endif
