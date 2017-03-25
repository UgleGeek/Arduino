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


// Define variables and constants


// Prototypes


// Utilities


// Functions
void scheduler(void);
void one_ms(unsigned long time_stamp);
void ten_ms(unsigned long time_stamp);
void hun_ms(unsigned long time_stamp);


// Add setup code
void setup()
{
    ;
}

// Add loop code
void loop()
{
    scheduler();
}

void scheduler(void)
{
    unsigned long time_now = 0;
    static unsigned long time_prev_one = 0;
    static unsigned long time_prev_ten = 0;
    static unsigned long time_prev_hun = 0;
    
    time_now = micros(); //millis();
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
    else if(time_now >= (time_prev_ten + 10))
    {
        time_prev_ten = time_now;
        ten_ms(time_now);
    }
    else if(time_now >= (time_prev_hun + 100))
    {
        time_prev_hun = time_now;
        hun_ms(time_now);
    }

}