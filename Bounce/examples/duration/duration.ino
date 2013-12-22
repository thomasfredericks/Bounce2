#include <Bounce.h>

#define BUTTON_PIN 2
#define LED_PIN 13

// Instantiate a Bounce object
Bounce debouncer = Bounce(); 

int buttonState;
unsigned long buttonPressTimeStamp;

void setup() {
  
  Serial.begin(57600);
  
  // Setup the button
  pinMode(BUTTON_PIN,INPUT);
  digitalWrite(BUTTON_PIN,HIGH);
  
  // After setting up the button, setup debouncer
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5);
  
  //Setup the LED
  pinMode(LED_PIN,OUTPUT);
  
}

void loop() {
 // Update the debouncer and get the changed state
  boolean changed = debouncer.update();


  
  if ( changed ) {
       // Get the update value
     int value = debouncer.read();
    if ( value == HIGH) {
       digitalWrite(LED_PIN, HIGH );
   
       buttonState = 0;
       Serial.println("Button released (state 0)");
   
   } else {
         digitalWrite(LED_PIN, LOW );
         buttonState = 1;
         Serial.println("Button pressed (state 1)");
         buttonPressTimeStamp = millis();
     
   }
  }
  
  if  ( buttonState == 1 ) {
    if ( millis() - buttonPressTimeStamp >= 2000 ) {
        buttonState = 2;
       Serial.println("Button held for two seconds (state 2)");
    }
  }
 
 
}

