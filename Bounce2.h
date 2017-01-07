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
  Previous contributions by Eric Lowry, Jim Schimpf and Tom Harkaway, Albert Phan
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifdef BOUNCE_LOCK
#error You are using the invalid BOUNCE_LOCK-OUT define. Please update your sources to use BOUNCE_LOCK_OUT
#endif

// Uncomment the following line for "LOCK-OUT" debounce method
//#define BOUNCE_LOCK_OUT


#ifndef Bounce2_h
#define Bounce2_h

#include <inttypes.h>

class Bounce
{
 public:
    // Create an instance of the bounce library
	Bounce(int pin, uint16_t interval_millis = 10, uint16_t interval_retrigger = 50, uint16_t interval_hold = 500);

    // Attach to a pin (and also sets initial state)
    void attach(int pin);
    
    // Attach to a pin (and also sets initial state) and sets pin to mode (INPUT/INPUT_PULLUP/OUTPUT)
    void attach(int pin, int mode);

    // Sets the debounce interval
    void interval(uint16_t interval_millis);

    // Changes the interval for held()
    void holdinterval(uint16_t interval_hold);
	
	// Changes the retrigger interval for retrigger()
	void retriggerinterval(uint16_t interval_retrigger);
	
	// Updates the pin
    // Returns 1 if the state changed
    // Returns 0 if the state did not change
    bool update();

    // Returns the updated pin state
    bool read();

    // Returns the falling pin state
    bool fell();

    // Returns the rising pin state
    bool rose();
	
	// Returns 1 if state has been held for held interval (default is 500ms)
	// Returns 0 if not
	bool held();
	
	// After the button has been held down, returns a 1 every interval_repeat(default is 50 ms)
	bool retrigger();

 protected:
    unsigned long previous_millis;
	unsigned long previous_millis_state_changed;
	uint16_t interval_hold;
	uint16_t interval_retrigger;
    uint16_t interval_millis;
    uint8_t state;
    uint8_t pin;
};

#endif
