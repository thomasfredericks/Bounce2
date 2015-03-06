/*
 External input example for the Bounce2 library
 
 This example demonstrates the advanced usage of the Bounce2 library. It reads
 an analog input from a potentiometer on pin A0. It then turns a LED on
 (pin 13) if the potentiometer is in the middle position for longer than
 3 seconds (the read value is between 312 and 712). The current values can
 be watched on the serial monitor.
 
 Why do you need this? Here's an example:
 Imagine this potentiometer (or another analog sensor) is attached to a door.
 You want to detect whether the door is kept closed. If you increase the debounce 
 time to maybe 10 seconds, everyone can pass the door without the debounced state 
 being changed. But if the door stands open for more than 10 seconds, the LED (or 
 an alarm) would be turned on.

 The circuit:
 * Potentiometer (10k):
   * center pin connected to pin A0
   * outside pins attached to +5V and ground
 * Built-in LED on pin 13
 
 Try the AnalogReadSerial example first if you don't know how a
 potentiometer works:
 http://arduino.cc/en/Tutorial/AnalogReadSerial
 
 This example code is in the public domain.
 
 */

#include <Bounce2.h>
 
Bounce bouncer = Bounce();

// helper function for checking whether the potentiometer
// is in the middle position
bool potentiometer_is_centered() {
  // read the analog value from pin A0
  int sensorValue = analogRead(A0);
  
  // return whether the value is between 312 and 712
  return sensorValue > 312 && sensorValue < 712;
}

void setup() {
  // start serial connection
  Serial.begin(9600);
  
  // configure the output LED
  pinMode(13, OUTPUT);
    
  // setup the Bounce object
  bool is_centered = potentiometer_is_centered();
  bouncer.init(is_centered);  // initialize with the current value
  bouncer.interval(3000);  // set the debounce time to 3000 ms (= 3 s)
}

void loop() {
  // determine the current state
  bool is_centered = potentiometer_is_centered();
  
  // update the bouncer
  bouncer.update(is_centered);
  
  // read the current debounced state
  int current_state = bouncer.read();

  // set the LED to the debounced state
  digitalWrite(13, current_state);
  
  // print the raw value
  // notice: this could differ from the value processed in potentiometer_is_centered()
  Serial.print("value: ");
  Serial.print(analogRead(A0));
  
  // print the current state
  Serial.print("\tis centered: ");
  Serial.print(is_centered ? "yes" : "no ");
  
  // print the debounced state
  Serial.print("\tdebounced: ");
  Serial.println(current_state == HIGH ? "yes" : "no ");
  
  delay(10);  // delay in between reads for stability
}
