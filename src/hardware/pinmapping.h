/**
 * @file pinmapping.h
 *
 * @brief Default GPIO pin mapping
 *
 */

#pragma once

/**
 * Input Pins
 */

// Switches/Buttons
#define PIN_POWERSWITCH 41 //VN
#define PIN_BREWSWITCH  25 //18
#define PIN_STEAMSWITCH 33 //19
#define PIN_WATERSWITCH 17 //VP 36



#define PIN_ROTARY_DT  42//27 // Rotary encoder data pin 4
#define PIN_ROTARY_CLK 43 // Rotary encoder clock pin
#define PIN_ROTARY_SW  48 // Rotary encoder switch

// Sensors
#define PIN_TEMPSENSOR  4   // war 16
#define PIN_FLOWESENSOR  19
#define PIN_WATERSENSOR  44//23
#define PIN_HXDAT       45//32 // Brew scale data pin 1
#define PIN_HXDAT2      46//25 // Brew scale data pin 2
#define PIN_HXCLK       47//33 // Brew scale clock pin

/**
 * Output pins
 */

// Relays
#define PIN_VALVE  53//17
#define PIN_PUMP 15 //27
#define PIN_HEATER 2
#define PIN_WATERBUTTONPOWER 16
#define PIN_BUTTON1POWER 12
#define PIN_BUTTON2POWER 14
#define PIN_HIGHPOWER1 27
#define PIN_HIGHPOWER2 26
#define PIN_HIGHPOWER3 5
#define PIN_LOWPOWER1 18



// LEDs
#define PIN_STATUSLED 49
#define PIN_BREWLED   50
#define PIN_STEAMLED  51

// Periphery
#define PIN_ZC 52 // Dimmer circuit Zero Crossing

/**
 * Bidirectional Pins
 */
#define PIN_I2CSCL 22
#define PIN_I2CSDA 21
