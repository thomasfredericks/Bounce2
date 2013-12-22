Bounce-Arduino-Wiring
=====================

Debouncing library for Arduino or Wiring
by Thomas Ouellet Fredericks
with contributions from:
Eric Lowry
Jim Schimpf
Tom Harkaway


Version
====================

1.6: Fixed for Arduino 1.0

1.5: Added risingEdge and fallingEdge

1.3: Fixed a bug that was confusing a local variable and an argument

1.2: Added a duration method

1.1: Removed a badly formated comment that would halt compiling

1.0: Initial Release

Description
====================

Bounce is a library for Arduino (arduino.cc). It debounces digital inputs and more (http://en.wikipedia.org/wiki/Debounce#Contact_bounce).


License
====================

MIT License (MIT)
Copyright (c) 2012 Thomas O Fredericks

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


Download, install and import
====================

• Put the Bounce folder in your Arduino "libraries".  To identify this location open "menu -> File -> Preferences". 


In the Arduino IDE, select "menubar->Sketch->Import Library->Bounce"  to import the library to your sketch. An "#include Bounce.h" line will appear  at the top of your Sketch.

You can also find examples under "menubar->File->Sketchbook->libraries->Bounce"


Methods
====================

# Bounce(byte pin,unsigned long debounce_interval)

Instantiates a Debounce object for the specified pin with a debounce time.

Because Bounce does not use interrupts, you have to "update" the object before reading its value.

# int update()

Updates Bounce. Returns true if the pin state changed (HIGH to LOW or LOW to HIGH). False if not.

# void interval(unsigned long interval) 

Changes the debounce time in milliseconds.


# int read()
Reads the updated pin state.

# void write(int state)
Sets the stored pin state 

# void rebounce(unsigned long interval)
Forces the pin to signal a state change in X milliseconds even if the state does not actually change.
Example: A button that repeats every X milliseconds as long as it is held down

# unsigned long duration(void)
Returns the number of milliseconds the pin has been in the current state.

# bool risingEdge()
// The risingEdge method is true for one scan after the de-bounced input goes from off-to-on.

# bool fallingEdge();
The fallingEdge  method it true for one scan after the de-bounced input goes from on-to-off. 

