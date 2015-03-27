
// Detect the falling edge

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce-Arduino-Wiring
#include <Bounce2.h>


#define BUTTON_PIN 2
#define LED_PIN 13

#define DEBOUNCE_TIME 5
#define HOLD_TIME 1000
#define RETRIGGER_TIME 100

int ledState = LOW;

// Instantiate a Bounce object with default values
Bounce debouncer(BUTTON_PIN);

// Or set your own values when instantiating Bounce object
// Bounce debouncer(BUTTON_PIN,DEBOUNCE_TIME, RETRIGGER_TIME, HOLD_TIME);


void setup() {
  
  // Setup the button with an internal pull-up :
  pinMode(BUTTON_PIN,INPUT);
  
  // Setup the LED :
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,ledState);
 
  
}

void loop() {

  // Update the Bounce instance :
   debouncer.update();
   
   // Call code if Bounce fell (transition from HIGH to LOW) :
   if ( debouncer.fell() ) {
      
     // Toggle LED state :
     ledState = !ledState;
     digitalWrite(LED_PIN,ledState);
     
   }
}

