#include "Bounce2Button.h"
bool BounceButton::read()
{
    return  getStateFlag(DEBOUNCED_STATE) ^ invert;
}

bool BounceButton::pressed()
{
    return (getStateFlag(DEBOUNCED_STATE) ^ invert) && getStateFlag(CHANGED_STATE);
}

bool BounceButton::released()
{
    return  !(getStateFlag(DEBOUNCED_STATE) ^ invert) && getStateFlag(CHANGED_STATE);
}
