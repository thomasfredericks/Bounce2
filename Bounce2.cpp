// Please read Bounce2.h for information about the liscence and authors


#include "Bounce2.h"

static const uint8_t DEBOUNCED_STATE = 0b00000001;
static const uint8_t UNSTABLE_STATE  = 0b00000010;
static const uint8_t CHANGED_STATE   = 0b00000100;


Bounce::Bounce()
    : previous_millis(0)
    , interval_millis(10)
    , state(0)
    , pin(0)
{}

void Bounce::attach(int pin) {
    this->pin = pin;
    state = 0;
    if (readCurrentState()) {
        setStateFlag(DEBOUNCED_STATE | UNSTABLE_STATE);
    }
#ifdef BOUNCE_LOCK_OUT
    previous_millis = 0;
#else
    previous_millis = millis();
#endif
}

void Bounce::attach(int pin, int mode){
    setPinMode(pin, mode);
    this->attach(pin);
}

void Bounce::interval(uint16_t interval_millis)
{
    this->interval_millis = interval_millis;
}

bool Bounce::update()
{

    unsetStateFlag(CHANGED_STATE);
#ifdef BOUNCE_LOCK_OUT
    
    // Ignore everything if we are locked out
    if (millis() - previous_millis >= interval_millis) {
        bool currentState = readCurrentState();
        if ( currentState != getStateFlag(DEBOUNCED_STATE) ) {
            previous_millis = millis();
            toggleStateFlag(DEBOUNCED_STATE);
            setStateFlag(CHANGED_STATE);
        }
    }
    

#elif defined BOUNCE_WITH_PROMPT_DETECTION
    // Read the state of the switch port into a temporary variable.
    bool readState = readCurrentState();


    if ( readState != getStateFlag(DEBOUNCED_STATE) ) {
      // We have seen a change from the current button state.

      if ( millis() - previous_millis >= interval_millis ) {
	// We have passed the time threshold, so a new change of state is allowed.
	// set the STATE_CHANGED flag and the new DEBOUNCED_STATE.
	// This will be prompt as long as there has been greater than interval_misllis ms since last change of input.
	// Otherwise debounced state will not change again until bouncing is stable for the timeout period.
	 toggleStateFlag(DEBOUNCED_STATE);
     setStateFlag(CHANGED_STATE );
      }
    }

    // If the readState is different from previous readState, reset the debounce timer - as input is still unstable
    // and we want to prevent new button state changes until the previous one has remained stable for the timeout.
    if ( readState != getStateFlag(UNSTABLE_STATE) ) {
	// Update Unstable Bit to macth readState
        toggleStateFlag(UNSTABLE_STATE);
        previous_millis = millis();
    }
    
    
#else
    // Read the state of the switch in a temporary variable.
    bool currentState = readCurrentState();
    

    // If the reading is different from last reading, reset the debounce counter
    if ( currentState != getStateFlag(UNSTABLE_STATE) ) {
        previous_millis = millis();
         toggleStateFlag(UNSTABLE_STATE);
    } else
        if ( millis() - previous_millis >= interval_millis ) {
            // We have passed the threshold time, so the input is now stable
            // If it is different from last state, set the STATE_CHANGED flag
            if (currentState != getStateFlag(DEBOUNCED_STATE) ) {
                previous_millis = millis();
                 toggleStateFlag(DEBOUNCED_STATE);
                 setStateFlag(CHANGED_STATE) ;
            }
        }

    
#endif

return  getStateFlag(CHANGED_STATE); 

}

bool Bounce::read()
{
    return  getStateFlag(DEBOUNCED_STATE);
}

bool Bounce::rose()
{
    return getStateFlag(DEBOUNCED_STATE) && getStateFlag(CHANGED_STATE);
}

bool Bounce::fell()
{
    return  !getStateFlag(DEBOUNCED_STATE) && getStateFlag(CHANGED_STATE);
}
