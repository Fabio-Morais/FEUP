#ifndef sa_h
#define sa_h

#include "Arduino.h"

// Arduino pin numbers for each LED
const byte LED_PINS[] = {13, 12, 11, 10};

// Shield
#define LED_D1_PIN 13
#define LED_D2_PIN 12
#define LED_D3_PIN 11
#define LED_D4_PIN 10

// Arduino pin numbers for each Push Button
const byte BUTTON_PINS[] = {A1, A2, A3};

// Define Pins for buttons
const int sens_in_pin     = A1;  // Button 
const int sens_out_pin    = A3;  // Button 


void init_hardware(void);
void write_number(int value);

// Timer Stuff
typedef struct {
  unsigned long start_time;
  unsigned long p;
  byte q;
} timer_t;


#endif
