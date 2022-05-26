
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
        updateTime();
    #endif
}


#ifdef BOUNCE_LOCK_OUT


bool Debouncer::update(){

    unsetStateFlag(CHANGED_STATE);

    // Ignore everything if we are locked out

    if(thresholdPassed()){

        bool currentState = readCurrentState();
      
        if(currentState != getStateFlag(DEBOUNCED_STATE)){
            updateTime();
            changeState();
        }
    }

	return changed(); 
}


#elif defined BOUNCE_WITH_PROMPT_DETECTION


bool Debouncer::update(){

    unsetStateFlag(CHANGED_STATE);


    /*
     *  Switch Port State 🠖 Temporary Variable
     */ 

    const bool state = readCurrentState();


    // Check if the button state has changed

    if(state != getStateFlag(DEBOUNCED_STATE)){

        /*
         *  Enough time has passed
         *  ⤷ New state changes are allowed
         * 
         *  Set Flags:
         *  - STATE_CHANGED
         *  - DEBOUNCED_STATE
         */

        if(thresholdPassed())
            changeState();
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

    if(state != getStateFlag(UNSTABLE_STATE)){

        // Update unstable bit to match readState

        toggleStateFlag(UNSTABLE_STATE);
        updateTime();
    }
        
	return changed(); 
}


#else


bool Debouncer::update(){

    unsetStateFlag(CHANGED_STATE);


    /*
     *  Switch Port State 🠖 Temporary Variable
     */

    const bool state = readCurrentState();
    

    /*
     *  If the reading ≠ to it's previous state
     *  ⤷ Reset the debounce counter
     */

    if(state != getStateFlag(UNSTABLE_STATE)){
        
        updateTime();
        toggleStateFlag(UNSTABLE_STATE);

        return changed();
    }

    if(thresholdPassed()){

        /*
         *  We have passed the threshold time
         *  ⤷ The input is now stable
         *   
         *  If it is ≠ to it's previous state
         *  ⤷ Set the STATE_CHANGED flag
         */

        if(state != getStateFlag(DEBOUNCED_STATE)){
            updateTime();
            changeState();
        }
    }

	return changed(); 
}


#endif



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


inline bool Debouncer::thresholdPassed(){
    return millis() - previous_millis >= interval_millis;
}

inline void Debouncer::updateTime(){
    previous_millis = millis();
}