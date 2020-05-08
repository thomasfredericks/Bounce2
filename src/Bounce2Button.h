#ifndef Bounce2Button_h
#define Bounce2Button_h

#include "Bounce2.h"
class BounceButton : public Bounce{
  public:
    BounceButton(){invert = false;}
    
    void setInvert(bool i){invert = i;}

    bool read();
    bool pressed();
    bool released();
    
  protected:
    bool invert;
};

#endif //Bounce2Button_h
