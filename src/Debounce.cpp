
/*
 *  Check Bounce2.h for licensing / authors.
 */

#include "Bounce2.h"


/*
 *  Debounce
 */

Debouncer::Debouncer():previous_millis(0)
    , interval_millis(10)
    , state(0) {}

void Debouncer::interval(uint16_t interval_millis){
    this -> interval_millis = interval_millis;
}


void Debouncer::begin(){

    state = 0;
    
    if(readCurrentState())
        setStateFlag(DEBOUNCED_STATE | UNSTABLE_STATE);

	#ifdef BOUNCE_LOCK_OUT
        previous_millis = 0;
    #else
        previous_millis = millis();
    #endif
}


bool Debouncer::update(){

    unsetStateFlag(CHANGED_STATE);

    #ifdef BOUNCE_LOCK_OUT
    
        // Ignore everything if we are locked out

        if (millis() - previous_millis >= interval_millis) {
            bool currentState = readCurrentState();
            if ( currentState != getStateFlag(DEBOUNCED_STATE) ) {
                previous_millis = millis();
                changeState();
            }
        }
        

    #elif defined BOUNCE_WITH_PROMPT_DETECTION

        /*
         *  Switch Port State 🠖 Temporary Variable
         */ 

        bool readState = readCurrentState();


        // Check if the button state has changed

        if(readState != getStateFlag(DEBOUNCED_STATE)){


            /*
             *  Enough time has passed
             *  ⤷ New state changes are allowed
             * 
             *  Set Flags:
             *  - STATE_CHANGED
             *  - DEBOUNCED_STATE
             */

            if(millis() - previous_millis >= interval_millis){
                changeState();
            }
        }


        /*
         *  If readState ≠ to it's previous state
         *  ⤷ Reset the debounce timer
         * 
         *  This is done, as input is still unstable
         *  and we want to prevent new button state 
         *  changes until the previous state has 
         *  remained stable for the timeout.
         */

        if(readState != getStateFlag(UNSTABLE_STATE)){

            // Update unstable bit to match readState

            toggleStateFlag(UNSTABLE_STATE);
            previous_millis = millis();
        }
        
    
    #else

        /*
         *  Switch Port State 🠖 Temporary Variable
         */

        bool currentState = readCurrentState();
        

        /*
         *  If the reading ≠ to it's previous state
         *  ⤷ Reset the debounce counter
         */

        if(currentState != getStateFlag(UNSTABLE_STATE)){
            previous_millis = millis();
            toggleStateFlag(UNSTABLE_STATE);
        } else
        if(millis() - previous_millis >= interval_millis){

            /*
             *  We have passed the threshold time
             *  ⤷ The input is now stable
             *   
             *  If it is ≠ to it's previous state
             *  ⤷ Set the STATE_CHANGED flag
             */

            if(currentState != getStateFlag(DEBOUNCED_STATE)){
              
                previous_millis = millis();
                
                changeState();
            }
        }

    
    #endif

	return  changed(); 
}


/*
 *  Work In Progress
 *  HELD
 */

unsigned long Debouncer::previousDuration() const {
	return durationOfPreviousState;
}


unsigned long Debouncer::currentDuration() const {
	return millis() - stateChangeLastTime;
}


inline void Debouncer::changeState(){

	toggleStateFlag(DEBOUNCED_STATE);
	setStateFlag(CHANGED_STATE) ;
	
    durationOfPreviousState = millis() - stateChangeLastTime;
	stateChangeLastTime = millis();
}


bool Debouncer::read() const {
    return getStateFlag(DEBOUNCED_STATE);
}


bool Debouncer::rose() const {
    return getStateFlag(DEBOUNCED_STATE) 
        && getStateFlag(CHANGED_STATE);
}


bool Debouncer::fell() const {
    return ! getStateFlag(DEBOUNCED_STATE) 
        &&   getStateFlag(CHANGED_STATE);
}
