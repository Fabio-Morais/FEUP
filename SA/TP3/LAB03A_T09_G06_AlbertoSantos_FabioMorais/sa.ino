#include "sa.h"
#include <TimerOne.h>

// Define shift register pins used for seven segment display
#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8

// Segment byte maps for numbers 0 to 9
const byte SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90};
// Byte maps to select digit 1 to 4
const byte SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

byte display_iterator;

void update_display(void)
{
  display_iterator++;
  if (display_iterator >= 4) 
    display_iterator = 0;

  display_segment(display_iterator);
}

//  Set DIO pins to outputs
void init_hardware(void)
{
  pinMode(LATCH_DIO,OUTPUT);
  pinMode(CLK_DIO,OUTPUT);
  pinMode(DATA_DIO,OUTPUT);

  pinMode(LED_PINS[0], OUTPUT);
  pinMode(LED_PINS[1], OUTPUT);
  pinMode(LED_PINS[2], OUTPUT);
  pinMode(LED_PINS[3], OUTPUT);
  
  pinMode(BUTTON_PINS[0], INPUT);
  pinMode(BUTTON_PINS[1], INPUT);
  pinMode(BUTTON_PINS[2], INPUT);

  Timer1.initialize(1000);  // 1000 us
  Timer1.attachInterrupt(update_display); // update_display to run every 1 ms
}



// Write a decimal number between 0 and 9999 to the display
void show_number(int value)
{
  if (value > 9999) value = 9999;
  if (value < 0) value = 0;
  write_number_to_segment(0, value / 1000);
  write_number_to_segment(1, (value / 100) % 10);
  write_number_to_segment(2, (value / 10) % 10);
  write_number_to_segment(3, value % 10);
}


byte segments[4];

// Wite a decimal number between 0 and 9 to one of the 4 digits of the display
void write_number_to_segment(byte Segment, byte Value)
{
  segments[Segment] = SEGMENT_MAP[Value];
}

void display_segment(byte Segment)
{
  digitalWrite(LATCH_DIO,LOW); 
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, segments[Segment]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment]);
  digitalWrite(LATCH_DIO,HIGH);    
}

// Wite a decimal number between 0 and 9 to one of the 4 digits of the display
void show_bits_in_segment(byte Segment, byte bits)
{
  segments[Segment] = ~bits;
}

// Bit Maping:
//
//   -0- 
//  5   1
//   -6-
//  4   2
//   -3-


// Timer Part
void start_timer(timer_t& T)
{
  T.start_time = millis();
  refresh_timer(T);
}


byte refresh_timer(timer_t& T)
{
  if(millis() - T.start_time > T.p * 100)  
    T.q = 1;
  else 
    T.q = 0;
}


