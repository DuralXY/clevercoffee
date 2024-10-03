/**
 * @file isr.h
 *
 * @brief Timer - ISR for PID calculation and heater relay output
 *
 */

#pragma once

#include "hardware/Relay.h"

extern double pidOutput;
extern hw_timer_t* timer;
extern Relay heaterRelay;
extern Relay pumpRelay;
bool pumpstrokes = false;

unsigned int isrCounter = 0; // counter for ISR
unsigned long windowStartTime;
unsigned int windowSize = 1000;
unsigned int flow = 0;
#define STROKETIME  200    // Time Stroke ms


void IRAM_ATTR gpioInterrupt() {
    flow = flow + 1;
}

void IRAM_ATTR onTimer() {
    timerAlarmWrite(timer, 10000, true);

    if (pidOutput <= isrCounter) {
        heaterRelay.off();
    }
    else {
        heaterRelay.on();
    }

    //Pumpstrokes 
    if (pumpstrokes) {               //Wenn Strokes on, wenn Dampf on, wenn wasser on?  
        if (STROKETIME <= isrCounter) {
                pumpRelay.off();
        }
        else {
                pumpRelay.on();
        }
    } 

    isrCounter += 10; // += 10 because one tick = 10ms

    // set PID output as relay commands
    if (isrCounter >= windowSize) {
        isrCounter = 0;
    }
}

/**
 * @brief Initialize hardware timers
 */
void initTimer1(void) {
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 10000, true);
}

void enableTimer1(void) {
    timerAlarmEnable(timer);
}

void disableTimer1(void) {
    timerAlarmDisable(timer);
}

bool isTimer1Enabled(void) {
    return timerAlarmEnabled(timer);
}
