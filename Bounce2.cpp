// Please read Bounce2.h for information about the liscence and authors

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Bounce2.h"

//This is an implementation detail that doesn't need to be seen by the outside world.
namespace {
    constexpr uint8_t DEBOUNCED_STATE = 0b00000001;
    constexpr uint8_t UNSTABLE_STATE  = 0b00000010;
    constexpr uint8_t STATE_CHANGED   = 0b00001000;
}

Bounce::Bounce() {
}

void Bounce::attach(uint8_t pin) {
    this->pin = pin;
    this->state = 0;
    if (digitalRead(pin)) {
        this->state = DEBOUNCED_STATE | UNSTABLE_STATE;
    }
    #ifdef BOUNCE_LOCK_OUT
        this->previous_millis = 0;
    #else
        this->previous_millis = millis();
    #endif
}

void Bounce::attach(uint8_t pin, uint8_t mode) {
    #if defined(ARDUINO_STM_NUCLEO_F103RB) || defined(ARDUINO_GENERIC_STM32F103C)
        pinMode(pin, (WiringPinMode)mode);
    #else
        pinMode(pin, mode);
    #endif
    this->attach(pin);
}

void Bounce::interval(uint16_t interval_millis) {
    this->interval_millis = interval_millis;
}

bool Bounce::update() {
#ifdef BOUNCE_LOCK_OUT
    this->state &= ~STATE_CHANGED;
    // Ignore everything if we are locked out
    if (millis() - this->previous_millis >= this->interval_millis) {
    #ifdef ANALOG_PINS
        this->value = analogRead(this->pin);
        bool currentState = (this->value > BouncerConstants::NOISE_TOLERANCE);
    #else
        bool currentState = digitalRead(this->pin);
    #endif
        if (currentState != (bool)(this->state & DEBOUNCED_STATE)) {
            this->previous_millis = millis();
            this->state ^= DEBOUNCED_STATE;
            this->state |= STATE_CHANGED;
        }
    }
    return this->state & STATE_CHANGED;

#elif defined BOUNCE_WITH_PROMPT_DETECTION
    // Read the state of the switch port into a temporary variable.
    #ifdef ANALOG_PINS
        this->value = analogRead(this->pin);
        bool currentState = (this->value > BouncerConstants::NOISE_TOLERANCE);
    #else
        bool currentState = digitalRead(this->pin);
    #endif
    // Clear Changed State Flag - will be reset if we confirm a button state change.
        this->state &= ~STATE_CHANGED;

    if (currentState != (bool)(state & DEBOUNCED_STATE)) {
        // We have seen a change from the current button state.
        if (millis() - this->previous_millis >= this->interval_millis) {
            // We have passed the time threshold, so a new change of state is allowed.
            // set the STATE_CHANGED flag and the new DEBOUNCED_STATE.
            // This will be prompt as long as there has been greater than interval_misllis ms since last change of input.
            // Otherwise debounced state will not change again until bouncing is stable for the timeout period.
            this->state ^= DEBOUNCED_STATE;
            this->state |= STATE_CHANGED;
        }
    }
    // If the currentState is different from previous currentState, reset the debounce timer - as input is still unstable
    // and we want to prevent new button state changes until the previous one has remained stable for the timeout.
    if (currentState != (bool)(this->state & UNSTABLE_STATE)) {
        // Update Unstable Bit to macth currentState
        this->state ^= UNSTABLE_STATE;
        this->previous_millis = millis();
    }
    // return just the sate changed bit
    return this->state & STATE_CHANGED;
#else
    // Read the state of the switch in a temporary variable.
    #ifdef ANALOG_PINS
        this->value = analogRead(this->pin);
        bool currentState = (this->value > BouncerConstants::NOISE_TOLERANCE);
    #else
        bool currentState = digitalRead(this->pin);
    #endif
    this->state &= ~STATE_CHANGED; ///reset STATE_CHANGED flag

    // If the reading is different from last reading, reset the debounce counter
    if (currentState != (bool)(this->state & UNSTABLE_STATE)) { /// PRESSED_STATE != UNSTABLE_STATE
        this->previous_millis = millis();
        this->state ^= UNSTABLE_STATE; ///XOR-on the UNSTABLE_STATE, reset all other flags
    }
    if (millis() - this->previous_millis >= this->interval_millis) { ///if enough time has passed
        // We have passed the threshold time, so the input is now stable
        // If it is different from last state, set the STATE_CHANGED flag
        if (currentState != (bool)(this->state & DEBOUNCED_STATE)) { ///PRESSED_STATE != DEBOUNCED_STATE
            this->previous_millis = millis();
            this->state ^= DEBOUNCED_STATE; /// XOR 0001 =>
            this->state |= STATE_CHANGED;   /// iOR 1000 => turn on the STATE_CHANGED flag
        }
    }
    return this->state & STATE_CHANGED; // return STATE_CHANGED flag
#endif
}

bool Bouncer::read() const { ///return if DEBOUNCED
    return (this->state & DEBOUNCED_STATE);
}

bool Bouncer::rose() const { ///return if DEBOUNCED and CHANGED
    return (this->state & DEBOUNCED_STATE) && (this->state & STATE_CHANGED);
}

bool Bouncer::fell() const { ///return if !DEBOUNCED or !CHANGED
    return !this->rose();
}

#ifdef ANALOG_PINS
uint16_t Bouncer::getValue() const {
    return this->value;
}
#endif
