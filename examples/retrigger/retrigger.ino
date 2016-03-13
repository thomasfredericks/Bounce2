
/*
DESCRIPTION
====================
Example of the retrigger() function of the Bounce 2 library. This function will retrigger a HIGH value after
the button has been held on for at least the hold interval (default 500 ms) and then retrigger every retrigger_interval afterwards (default 50ms)
This function is great for editing values without repeatedly pressing the button.
Open the Serial Monitor (57600 baud) for debug messages.

*/

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce-Arduino-Wiring

#include <Bounce2.h>

#define BUTTON_PIN 2
#define LED_PIN 13

#define DEBOUNCE_TIME 5
#define HOLD_TIME 1000
#define RETRIGGER_TIME 100

// Instantiate a Bounce object with default values
Bounce debouncer(BUTTON_PIN);

// Or set your own values when instantiating Bounce object
// Bounce debouncer(BUTTON_PIN,DEBOUNCE_TIME, RETRIGGER_TIME, HOLD_TIME);

unsigned long buttonPressTimeStamp;
unsigned char ledState = 0;

void setup() {
	Serial.begin(57600);
	
	// Setup the button
	pinMode(BUTTON_PIN,INPUT);
	
	//Setup the LED
	pinMode(LED_PIN,OUTPUT);
	digitalWrite(LED_PIN,LOW);
	
}

void loop() {
	// Update the debouncer
	debouncer.update();

	// If button had a rising transition, turn on led.
	if(debouncer.rose())
	{
		ledState = 1;
		digitalWrite(LED_PIN, ledState);
		buttonPressTimeStamp = millis();
		Serial.print(buttonPressTimeStamp);
		Serial.println(" Button rose!");
	}
	// After holding down the button, retrigger returns a 1 every interval_hold (default = 50 ms)
	if (debouncer.retrigger())
	{
		buttonPressTimeStamp = millis();
		Serial.print(buttonPressTimeStamp);
		Serial.println(" Button retriggered!");
		
		ledState = !ledState;
		digitalWrite(LED_PIN, ledState);
	}
	// When button has a falling transition, turn off led.
	if(debouncer.fell())
	{
		ledState = 0;
		digitalWrite(LED_PIN, ledState);
		buttonPressTimeStamp = millis();
		Serial.print(buttonPressTimeStamp);
		Serial.println(" Button fell!");
	}

	
}


