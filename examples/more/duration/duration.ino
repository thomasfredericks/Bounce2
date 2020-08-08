/* 
DESCRIPTION
====================
Reports through serial (57600 baud) the time since 
a button press (transition from HIGH to LOW).

*/

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>


#define BUTTON_PIN 2
#define LED_PIN 13

// Instantiate a Bounce object :
Bounce debouncer = Bounce(); 

unsigned long buttonPressTimeStamp;

void setup() {
  
  Serial.begin(57600);
  
  // Setup the button with an internal pull-up :
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  
  // After setting up the button, setup the Bounce instance :
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5);
  
  // Setup the LED :
  pinMode(LED_PIN,OUTPUT);
  
}

void loop() {
  
   // Update the Bounce instance :
  debouncer.update();

  // Call code if Bounce fell (transition from HIGH to LOW) :
  if ( debouncer.fell()  ) {;
  
    Serial.println( millis()-buttonPressTimeStamp );
     buttonPressTimeStamp = millis();
  
  }
  

}

