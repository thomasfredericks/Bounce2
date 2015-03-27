// Please read Bounce2.h for information about the liscence and authors

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Bounce2.h"

#define DEBOUNCED_STATE 0
#define UNSTABLE_STATE  1
#define STATE_CHANGED   3
#define STATE_HELD_ON	4
#define FIRSTUPDATE     5


Bounce::Bounce(int pin, uint16_t interval_millis, uint16_t interval_retrigger, uint16_t interval_hold)
{
	this->pin = pin;
	interval(interval_millis);
	holdinterval(interval_hold);
	retriggerinterval(interval_retrigger);
	previous_millis_state_changed = 0;
	state = _BV(FIRSTUPDATE);
}

void Bounce::attach(int pin) {
	this->pin = pin;
	bool read = digitalRead(pin);
	state = 0;
	if (digitalRead(pin)) {
		state = _BV(DEBOUNCED_STATE) | _BV(UNSTABLE_STATE);
	}
	#ifdef BOUNCE_LOCK_OUT
	previous_millis = 0;
	#else
	previous_millis = millis();
	#endif
}

void Bounce::interval(uint16_t interval_millis)
{
	this->interval_millis = interval_millis;
}

void Bounce::holdinterval(uint16_t interval_hold)
{
	this->interval_hold = interval_hold;
}

void Bounce::retriggerinterval(uint16_t interval_retrigger)
{
	this->interval_retrigger = interval_retrigger;
}

bool Bounce::update()
{
	// Attaches the pin the first time update is called
	if(state & _BV(FIRSTUPDATE))
	{
		attach(pin);
		state &= _BV(FIRSTUPDATE);
	}
	else
	{
		#ifdef BOUNCE_LOCK_OUT
		state &= ~_BV(STATE_CHANGED);
		// Ignore everything if we are locked out
		if (millis() - previous_millis >= interval_millis) {
			bool currentState = digitalRead(pin);
			if ((bool)(state & _BV(DEBOUNCED_STATE)) != currentState) {
				previous_millis = millis();
				state ^= _BV(DEBOUNCED_STATE);
				state |= _BV(STATE_CHANGED);
			}
		}
		return state & _BV(STATE_CHANGED);
		#else
		// Read the state of the switch in a temporary variable.
		bool currentState = digitalRead(pin);
		state &= ~_BV(STATE_CHANGED);

		// If the reading is different from last reading, reset the debounce counter
		if ( currentState != (bool)(state & _BV(UNSTABLE_STATE)) ) {
			previous_millis = millis();
			state ^= _BV(UNSTABLE_STATE);
		} else
		if ( millis() - previous_millis >= interval_millis ) {
			// We have passed the threshold time, so the input is now stable
			// If it is different from last state, set the STATE_CHANGED flag
			if ((bool)(state & _BV(DEBOUNCED_STATE)) != currentState) {
				previous_millis = millis();
				state ^= _BV(DEBOUNCED_STATE);
				state |= _BV(STATE_CHANGED);
			}
		}

		
		#endif
		
		//code for checking if state has been held on >= 500ms or interval_hold
		
		// If state has changed and has not been held on previously
		if(state & _BV(STATE_CHANGED) && !(state & _BV(STATE_HELD_ON)))
		{
			//If state has been changed before 500ms since last change, reset state change timer
			if(millis() - previous_millis_state_changed < interval_hold)
			{
				previous_millis_state_changed = 0;
			}
			else
			{
				previous_millis_state_changed = millis();
			}
		}
		// If state has changed and has been held on previously
		else if(state & _BV(STATE_CHANGED) && (state & _BV(STATE_HELD_ON)))
		{
			// Immediately turn off held on state
			state &= ~_BV(STATE_HELD_ON);
			previous_millis_state_changed = 0;
		}
		else if(previous_millis_state_changed != 0)
		{
			//if button has been at a debounced state for >= 500ms
			if(millis() - previous_millis_state_changed >= interval_hold)
			{
				state |= _BV(STATE_HELD_ON);
				previous_millis_state_changed = 0;
			}
		}
		return state & _BV(STATE_CHANGED);
	}
}

bool Bounce::retrigger()
{
	// if button is being held
	if(this->held())
	{
		if(previous_millis_state_changed != 0)
		{
			// Checks if it has been longer that retrigger time
			if (millis() - previous_millis_state_changed >= interval_retrigger)
			{
				previous_millis_state_changed = millis();
				return true;
			}
		}
		else
		{
			// sets the millis when first going into function
			previous_millis_state_changed = millis();
			return false;
			
		}
	}
}


bool Bounce::read()
{
	return state & _BV(DEBOUNCED_STATE);
}

bool Bounce::rose()
{
	return ( state & _BV(DEBOUNCED_STATE) ) && ( state & _BV(STATE_CHANGED));
}

bool Bounce::fell()
{
	return !( state & _BV(DEBOUNCED_STATE) ) && ( state & _BV(STATE_CHANGED));
}

bool Bounce::held()
{
	return (state & _BV(STATE_HELD_ON));
}
