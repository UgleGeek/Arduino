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


void one_ms(unsigned long tick);
void led(int val);

static int cycle_time = 2000;
static int time_slice_time = 1;
static bool state_on = false;




void setup()
{
    pinMode(13, OUTPUT);
}

void loop()
{
    static unsigned long time_now, time_prev = 0;
    
    time_now = millis();
    if(time_now >= (time_prev + time_slice_time))
    {
        time_prev = time_now;
        one_ms(time_now);
    }
}



void one_ms(unsigned long tick)
{
    static int out = 0;
    static int cycle = 0;
    const int increment = 25500/cycle_time;
    
    if(cycle++ >= cycle_time)
    {
        cycle = 0;
        state_on = !state_on;
    }
    
    if(state_on)    out += increment;
    else            out -= increment;
    
    if(out > 25500) out = 25500;
    if(out < 500)   out = 500;
    
    led(out/100);
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