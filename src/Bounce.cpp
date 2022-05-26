
/*
 *  Check Bounce2.h for licensing / authors.
 */

#include "Bounce2.h"


/*
 *  Bounce
 */

Bounce::Bounce()
    : pin(0)
{}

void Bounce::attach(int pin) {
    this->pin = pin;
    
    // Set Initial State

    begin();
}

void Bounce::attach(int pin, int mode){
    setPinMode(pin, mode);
    this->attach(pin);
}
