////////////
// BOUNCE //
////////////


Bounce::Bounce()
    : pin(0)
{}

void Bounce::attach(int pin) {
    this->pin = pin;
    
    // SET INITIAL STATE
    begin();
}

void Bounce::attach(int pin, int mode){
    setPinMode(pin, mode);
    this->attach(pin);
}
