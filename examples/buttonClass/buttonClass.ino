


/* 
 DESCRIPTION
 ====================
 Simple example of the Button class from the Bounce library.
 The Button class matches an electrical state to a physical action.
 that switches the debug LED when 
 either of 2 buttons are pressed.
 */
 
// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#define BUTTON_PIN_A 2
#define BUTTON_PIN_B 3


#define LED_PIN LED_BUILTIN

// Instantiate a Button object
Button buttonA = Button(); 

// Instantiate another Button object
Button buttonB = Button(); 

void setup() {

  // SETUP BUTTON A
  buttonA.attach( BUTTON_PIN_A , INPUT_PULLUP );
  buttonA.interval(5); // interval in ms
  buttonA.setPressedState(LOW); // INDICATE THAT THE LOW STATE CORRESPONDS TO PHYSICALLY PRESSING THE BUTTON
  
  // SETUP BUTTON B
  buttonB.attach( BUTTON_PIN_B , INPUT_PULLUP );
  buttonB.interval(5); // interval in ms
  buttonB.setPressedState(LOW); // INDICATE THAT THE LOW STATE CORRESPONDS TO PHYSICALLY PRESSING THE BUTTON


  // SETUP LED
  pinMode(LED_PIN,OUTPUT);

}

void loop() {
  // UPDATE THE BUTTONS
  buttonA.update();
  buttonB.update();


  // TOGGLE THE LED IF EITHER BUTTON IS PRESSED
  if ( buttonA.pressed()  || buttonB.pressed()  ) {
    digitalWrite(LED_PIN,  !digitalRead(LED_PIN)  );
  } 


}
