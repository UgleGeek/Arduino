//
// Hackintosh2
//
// Description of the project
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author 		Erik Steen Sørensen
// 				Erik Steen Sørensen
//
// Date			25/03/17 12:35
// Version		<#version#>
//
// Copyright	© Erik Steen Sørensen, 2017
// Licence		<#licence#>
//
// See         ReadMe.txt for references
//


// Core library for code-sense - IDE-based
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(ESP8266) // ESP8266 specific
#include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.8 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

// Set parameters


// Include application, user and local libraries


// Define structures and classes
enum pc_state {OFF, ON, SLEEP};

// Define variables and constants
#define POWER_LED 3
#define POWER_IN 4
#define PCB_LED 13
#define INCREMENT 20
#define DEADTIME 200
#define INPULSE 1000
#define OFF_VAL 0
#define ON_VAL 25500
#define SLEEP_VAL 6400

pc_state inState, outState;
// Prototypes


// Utilities


// Functions
void scheduler(void);
void one_ms(unsigned long time_stamp);
void ten_ms(unsigned long time_stamp);
void hun_ms(unsigned long time_stamp);
void handle_power_out(int taskdur);
void handle_power_in(int taskdur);

// ----------------------------------------------------------------------------

void setup()
{
    inState = OFF;
    outState = OFF;
    pinMode(POWER_LED, OUTPUT);
    pinMode(POWER_IN, INPUT);
    pinMode(PCB_LED, INPUT);
    pinMode(2, INPUT); // temporary
}

void one_ms(unsigned long time_stamp)
{
    ;
}

// ----------------------------------------------------------------------------

void ten_ms(unsigned long time_stamp)
{
    handle_power_in(10);
    handle_power_out(100);
}

// ----------------------------------------------------------------------------

void hun_ms(unsigned long time_stamp)
{
  ;
}

// ----------------------------------------------------------------------------

void handle_power_out(int taskdur)
{
    static int out = 0;
    static int cntr = 0;
    static int increment_sign = 1;
    
    if(outState == OFF)
    {
        out -= INCREMENT * 10;
        
        if(out < OFF_VAL) // reached OFF
        {
            out = OFF_VAL;
            outState = inState; // match instate
        }
    }
    else if(outState == ON)
    {
        out += INCREMENT * 10;
        
        if(out > ON_VAL) // reached ON
        {
            out = ON_VAL;
            outState = inState; // match instate
        }
    }
    else // outState == SLEEP
    {
        out += INCREMENT * increment_sign;
        
        if(out > SLEEP_VAL) // reached SLEEP max
        {
            out = SLEEP_VAL;
            increment_sign = -1;
            outState = inState; // match instate
        }
        else if(out < OFF_VAL) // reached SLEEP min
        {
            out = OFF_VAL;
            increment_sign = 1;
            outState = inState; // match instate
        }
    }
    analogWrite(POWER_LED, out/100);
}

// ----------------------------------------------------------------------------

void handle_power_in(int taskdur)
{
    static int cntr = 0;
    static int fcntr = 0;
    static bool prev_inp = false;
    bool inp;
    
    inp = digitalRead(POWER_IN);
    
 //   if(inp) digitalWrite(PCB_LED, true);
 //   else digitalWrite(PCB_LED, false);
    
    
    if(inp != prev_inp)
    {
        fcntr++;
        prev_inp = inp;
    }
    
    if(cntr++ >= INPULSE/taskdur)
    {
        if(fcntr > 1)
        {
            inState = SLEEP;
        }
        else if(inp == true)
        {
            inState = ON;
        }
        else
        {
            inState = OFF;
        }
        fcntr = 0;
        cntr = 0;
    }


        if(inp != 0) digitalWrite(PCB_LED, true);
        else digitalWrite(PCB_LED, false);   
}

// ----------------------------------------------------------------------------

void scheduler(void)
{
    unsigned long time_now = 0;
    static unsigned long time_prev_one = 0;
    static unsigned long time_prev_ten = 0;
    static unsigned long time_prev_hun = 0;
          static bool toggle = false;

    
    time_now = millis(); //millis();
    if(time_prev_one > time_now)
    {
        time_prev_one = 0;
        static unsigned long time_prev_one =   1;
        static unsigned long time_prev_ten =  10;
        static unsigned long time_prev_hun = 100;
    }
    
    if(time_now >= (time_prev_one + 1))
    {
        time_prev_one = time_now;
        one_ms(time_now);
    }
    
    if(time_now >= (time_prev_ten + 10))
    {
        time_prev_ten = time_now;
        ten_ms(time_now);
    }
    
    if(time_now >= (time_prev_hun + 100))
    {
        time_prev_hun = time_now;
        hun_ms(time_now);

    }

}

// ----------------------------------------------------------------------------

void loop()
{

    scheduler();

}

