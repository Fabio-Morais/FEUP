/////////////////////////////////////////////////
// Sistemas e Automação                        //  
// (C) FEUP paco@fe.up.pt and asousa@fe.up.pt  //
/////////////////////////////////////////////////


#include <Arduino.h> 

#include "two_byj48.h"
#include "proj_types.h" 


#define pin_SW_top A0 
#define pin_SW_bot A1 
byte SW_top;
byte SW_bot;
int motor_angle;
int cap=4; //capacidade do parque
int n; //carros no parque
byte state0,state1,state2,state3,state4,state5,state6,state7,state8,state9,state10;


// Define 8 global timers
const int total_timers  = 8;
timer_t timer[total_timers];


// To be updated by read_inputs at start of cycle 
byte sens_in;
byte sens_out;
byte sens_vert;
byte sens_horiz;

// To be updated by write_outputs at end of cycle 
byte sign_red;
byte sign_green;
byte led_sens_horiz;
byte led_sens_vert;

byte motor_enable, motor_up, motor_down;

// Input PINs =====> Rectify with your own pins if needed
const int pin_sens_in   = 7;  
const int pin_sens_out  = 6;

// OUTPUT PINs =====> Rectify with your own pins if needed
const int pin_green    = 5;
const int pin_red      = 4;
const int pin_led_sens_vert  = 3;
const int pin_led_sens_horiz = 2;

int motor_nominal_speed = 500;

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

// Update timers
void refresh_timers(void)
{
 byte i;
 for(i = 0; i < total_timers; i++)
   refresh_timer(timer[i]);
}

// Read from pins to positive “Image_Variables”
void read_inputs(void)
{
  sens_in = !digitalRead(pin_sens_in );
  sens_out = !digitalRead(pin_sens_out);
  SW_top = digitalRead(pin_SW_top);
  SW_bot = digitalRead(pin_SW_bot);
  motor_angle = -90.0 * get_motor_pos(0) / 1000.0; 

  sens_horiz = motor_angle < 0;
  sens_vert = motor_angle > 90;
} // End of read_inputs()


// Write to pins from “Image_Variables”
void write_outputs(void)
{
  digitalWrite(pin_green, sign_green);
  digitalWrite(pin_red, sign_red);
  digitalWrite(pin_led_sens_vert, led_sens_vert);
  digitalWrite(pin_led_sens_horiz, led_sens_horiz);

  if (motor_enable) {
    if (motor_up) {
      set_motor_req_speed(0, -motor_nominal_speed);
      set_motor_speed(0, -motor_nominal_speed);
    } else if (motor_down) {
      set_motor_req_speed(0, motor_nominal_speed);
      set_motor_speed(0, motor_nominal_speed);
    } else {
      set_motor_req_speed(0, 0);
      set_motor_speed(0, 0);
    }
  } else {
    set_motor_req_speed(0, 0);
    set_motor_speed(0, 0);
  }  
} // End of write_outputs

void set_motor_up(void)
{
   motor_up = 1;
   motor_down = 0;
   motor_enable = 1;
}

void set_motor_down(void)
{
   motor_up = 0;
   motor_down = 1;
   motor_enable = 1;
}

void set_motor_stop(void)
{
   motor_up = 0;
   motor_down = 0;
   motor_enable = 0;
}


/* The setup routine runs once when you press reset: */
void setup() 
{        
  state2=1;
  state4=1;
  state6=1;
  n=0;
  
  // Initialize serial
  Serial.begin(115200);
  // Init message
  Serial.println("FEUP - S&A - Init Lab04");
  
  // Define Input and Output Pins
  pinMode(pin_green, OUTPUT);     
  pinMode(pin_red, OUTPUT);     
  pinMode(pin_led_sens_vert, OUTPUT);     
  pinMode(pin_led_sens_horiz, OUTPUT);     
  pinMode(pin_sens_in, INPUT_PULLUP); 
  pinMode(pin_sens_out, INPUT_PULLUP); 

  pinMode(pin_SW_top, INPUT_PULLUP); 
  pinMode(pin_SW_bot, INPUT_PULLUP); 
  
  digitalWrite(pin_green, HIGH);    delay(200);    // Leds one at a time
  digitalWrite(pin_red, HIGH);      delay(200);    // Leds one at a time
  digitalWrite(pin_led_sens_vert, HIGH);   delay(200);    // Leds one at a time
  digitalWrite(pin_led_sens_horiz, HIGH); delay(200);    // Leds one at a time
  
  two_byj48_init();

  // Setup Timers Here!
  timer[0].p = 1; // 0.1 seconds
  timer[2].p = 30; //tempo para entrar em erro
  timer[3].p = 10; //freq de pisca pisca 
  start_timer(timer[0]);


  digitalWrite(pin_green, LOW);
  digitalWrite(pin_red, LOW);
  digitalWrite(pin_led_sens_vert, LOW);
  digitalWrite(pin_led_sens_horiz, LOW);
  
  Serial.println("Init done"); 

  byte init_state = 0;
  while(1) {
     refresh_timers();
     read_inputs();

     if ((init_state == 0) && SW_top) {
       init_state = 1;  
       set_motor_pos(0, -1205);
       timer[1].p = 20; // 1 second
       start_timer(timer[1]);
     } else if ((init_state == 1) && timer[1].q) {
       init_state = 2;  
     }
     
     if (init_state == 0) set_motor_up();
     else if (init_state == 1) set_motor_down();
     else if (init_state == 2) {
       set_motor_stop();
       break;
     }

     write_outputs();
  }
}


long previousMicros = 0; 


void loop() 
{
  unsigned long currentMicros = micros();
  if(currentMicros - previousMicros > 10000) {   // 10 ms
    refresh_timers();
    read_inputs();

    loop_10ms();
 
    // End Switch protection
    //motor_up = motor_up && !SW_top;
    //motor_down = motor_down && !SW_bot;
    
    motor_enable = motor_enable && !SW_bot  && !SW_top;
  
    write_outputs();
  }
  
  // Output debug every 0.1 s
  if (timer[0].q) {
    start_timer(timer[0]);
/*
    Serial.print(motor_enable);
    Serial.print(motor_up);
    Serial.print(motor_down);
    
    Serial.print("  ");

    Serial.print("  ");
    Serial.print(motor_angle);

    Serial.println();*/

Serial.println( " St0:"    + ((String) state0) +" St1:"   + ((String) state1)    + " St2:"    + ((String) state2) +  " St3:"    + ((String) state3)+  " St4:"    + ((String) state4) +  " St5:"    + ((String) state5)+ " St6:"    + ((String) state6)+ " St7:"    + ((String) state7)+ " St8:"    + ((String) state8)+ 
                  " Sens:" + ((String) sens_in  ) + ((String) sens_out ) +
                  " Sign:" + ((String) sign_green) + ((String) sign_red) +
                  " sensvert/horiz:" + ((String) sens_vert)   + ((String) sens_horiz));
   Serial.println(n);

    
  }    
  
}



///////////////////////////////////////////////////
///////                                     ///////   
///////   Write Your Code below this line   ///////
///////                                     ///////   
///////  Comment or delete example code!!!  ///////   
///////                                     ///////   
///////////////////////////////////////////////////



void loop_10ms(void) 
{

              /* OUTPUTS*/
  motor_up     = (state1==1);
  motor_down   = (state3==1);
  motor_enable = (state1==1||state3==1);
  sign_green   = (state4==1&&state8==0) || state9 ;
  sign_red     = (state5==1&&state8==0) || state10;
  led_sens_horiz = sens_horiz;
  led_sens_vert = sens_vert;
 

  
  if(state0&&sens_in&&n<cap&&!state8){
      state0=0;
      state1=1;
  }
  if(state1&&sens_vert){
      state1=0;
      state2=1;
      n++;      // numero de carros atual, incrementa

  }
  if(state2&&(!sens_in)){
      state2=0;
      state3=1;
  }
  if(state3&&sens_horiz){
      state3=0;
      state0=1;
      
  }
  if(state4&&n==cap){
      state4=0;
      state5=1;
  }
  if(state5&&n<cap){
      state5=0;
      state4=1;
  }
  if(state6&&n>0&&sens_out){
      state6=0;
      state7=1;
      start_timer(timer[2]);
      n--;
  }
  if(state7&&!sens_out){
      state7=0;
      state6=1;
  }
  if(state7&&sens_out&&timer[2].q){
      state7=0;
      state8=1;
      state9=1;
      start_timer(timer[3]);
  }
  if(state8&&!sens_out){          //STATE 8 - ERROR
      state8=0;
      state6=1;
      state10=0;
      state9=0;
  }
 
    
  if(state9 &&timer[3].q){      // estado 9 e 10 serve para conseguirmos piscar o verde e vermelho
      refresh_timers();
      start_timer(timer[3]);
      state10=1;
      state9=0;
      }
    if(state10 &&timer[3].q){
      refresh_timers();
      start_timer(timer[3]);
      state9=1;
      state10=0;
      }
  
  // End of your code
 
}  



