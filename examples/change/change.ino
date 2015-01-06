
// Detect the falling edge

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce-Arduino-Wiring
#include <Bounce2.h>


#define BUTTON_PIN 2
#define LED_PIN 13

int ledState = LOW;


// Instantiate a Bounce object :
Bounce debouncer = Bounce(); 

void setup() {
  
  // Setup the button with an internal pull-up :
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  
  // After setting up the button, setup the Bounce instance :
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(500);
  
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

