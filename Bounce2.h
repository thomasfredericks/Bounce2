/*
  The MIT License (MIT)

  Copyright (c) 2013 thomasfredericks

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
  Main code by Thomas O Fredericks (tof@t-o-f.info)
  Previous contributions by Eric Lowry, Jim Schimpf and Tom Harkaway
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef Bounce2_h
#define Bounce2_h

// Uncomment the following line for analog pins in use
//#define ANALOG_PINS

// Uncomment the following line for "LOCK-OUT" debounce method
//#define BOUNCE_LOCK_OUT

// Uncomment the following line for "BOUNCE_WITH_PROMPT_DETECTION" debounce method
//#define BOUNCE_WITH_PROMPT_DETECTION

#include <inttypes.h>

namespace BouncerConstants {
    constexpr uint16_t NOISE_TOLERANCE = 50;
}

class Bounce
{
public:
    // Create an instance of the bounce library
    Bounce();

    // Attach to a pin (and also sets initial state)
    void attach(uint8_t pin);
    
    // Attach to a pin (and also sets initial state) and sets pin to mode (INPUT/INPUT_PULLUP/OUTPUT)
    void attach(uint8_t pin, uint8_t mode);

    // Sets the debounce interval
    void interval(uint16_t interval_millis);

    // Updates the pin
    // Returns whether the state changed or not
    bool update();

    // Returns the updated pin state
    bool read() const;

    // Returns the falling pin state
    bool fell() const;

    // Returns the rising pin state
    bool rose() const;

#ifdef ANALOG_PINS
    // Returns the updated pin value
    uint16_t getValue() const;
#endif

    // Partial compatibility for programs written with Bounce version 1
    bool risingEdge() { return rose(); }
    bool fallingEdge() { return fell(); }
    Bounce(uint8_t pin, unsigned long interval_millis ) : Bounce() {
        attach(pin);
        interval(interval_millis);
    }

protected:
    unsigned long previous_millis = 0;
    uint16_t interval_millis = 10;
#ifdef ANALOG_PINS
    uint16_t value = 0;
#endif
    uint8_t state = 0;
    uint8_t pin = 0;
};

#endif
