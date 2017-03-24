//
// blinky
//
// blinking lights
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author 		Erik Steen Sørensen
// 				Erik Steen Sørensen
//
// Date			20/03/17 21:05
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


void one_ms(unsigned long time_ms);
void led(int val);

static int cycle_time = 3000;
static int time_slice_time = 1000;
static bool state_on = true;
int led_value = 0;




void setup()
{
    pinMode(13, OUTPUT);
}

void loop()
{
    static unsigned long time_now, time_prev = 0;
    
    time_now = micros(); //millis();
    if(time_now >= (time_prev + time_slice_time))
    {
        time_prev = time_now;
        one_ms(time_now/time_slice_time);
    }
    if(time_prev > time_now) time_prev = 0;

    led(led_value);
}



void one_ms(unsigned long time_ms)
{
    static int out = 0;
    static int cycle = 0;
    const int increment = 25500/cycle_time;
    static unsigned long time_old = 0;
    
    if(time_ms >= (time_old + cycle_time))
    {
        time_old = time_ms;
        state_on = !state_on;
    }   
    if(time_old > time_ms) time_old = 0;



    if(state_on)    out += increment;
    else            out -= increment;
    
    if(out > 25500) out = 12800;
    if(out < 0)   out = 0;
    
    led_value = out/100;
}


void led(int val)
{
    static int err = 0;
    int out;
    
    if(val > 255) val = 255;
    out = val + err;
    
    if(out > 127)
    {
        digitalWrite(13, true);
        err = out - 255;
    }
    else
    {
        digitalWrite(13, false);
        err = out;
    }
    
}

