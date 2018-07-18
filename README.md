# BOUNCE 2

Debouncing library for Arduino and Wiring by Thomas Ouellet Fredericks with contributions from: Eric Lowry, Jim Schimpf, Tom Harkaway, Joachim Krüger and MrGradgrind.

More about debouncing: http://en.wikipedia.org/wiki/Debounce#Contact_bounce

See the bottom of this page for a basic usage example and the "examples" folder for more.

## GITHUB PAGE

https://github.com/thomasfredericks/Bounce2

## DOCUMENTATION

The complete class documentation can be found in the "docs" folder or [online here](http://thomasfredericks.github.io/Bounce2/).

# HAVE A QUESTION?

Please post your questions [here](http://forum.arduino.cc/index.php?topic=266132.0).

# INSTALLATION & DOWNLOAD

Install through your software's Library Manager or download the latest version [here](https://github.com/thomasfredericks/Bounce2/archive/master.zip) and put the "Bounce2" folder in your "libraries" folder. 

The original version of Bounce (Bounce 1) is included in the download but not supported anymore.


# DEBOUNCE ALGORITHMS (FOR ADVANCED USERS)


## STABLE INTERVAL

By default, the Bounce library uses a stable interval to process the debouncing. This is simpler to understand and can cancel unwanted noise.

![](https://raw.github.com/thomasfredericks/Bounce-Arduino-Wiring/master/extras/BouncySwitch_stable.png)

## LOCK-OUT INTERVAL

By defining "#define BOUNCE_LOCK_OUT" in "Bounce.h" (or in your code before including "Bounce.h") you can activate an alternative debouncing method. This method is a lot more responsive, but does not cancel noise.

```
#define BOUNCE_LOCK_OUT
```

![](https://raw.github.com/thomasfredericks/Bounce-Arduino-Wiring/master/extras/BouncySwitch_lockout.png)


## WITH PROMPT DETECTION

By defining "#define BOUNCE_WITH_PROMPT_DETECTION" in "Bounce.h" (or in your code before including "Bounce.h") you can activate an alternative debouncing method. Button state changes are available immediately so long as the previous state has been stable for the timeout period. Otherwise the state will be updated as soon as  the timeout period allows.

* Able to report acurate switch time normally with no delay.
* Use when accurate switch transition timing is important.

```
#define BOUNCE_WITH_PROMPT_DETECTION
```

# BASIC EXAMPLE

```cpp
// This example toggles the debug LED (pin 13) on or off
// when a button on pin 2 is pressed.

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#define BUTTON_PIN 2
#define LED_PIN 13

int ledState = LOW;


Bounce debouncer = Bounce(); // Instantiate a Bounce object

void setup() {
  
  debouncer.attach(BUTTON_PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer.interval(25); // Use a debounce interval of 25 milliseconds
  
  
  pinMode(LED_PIN,OUTPUT); // Setup the LED
  digitalWrite(LED_PIN,ledState);
 
}

void loop() {

   debouncer.update(); // Update the Bounce instance
   
   if ( debouncer.fell() ) {  // Call code if button transitions from HIGH to LOW
     ledState = !ledState; // Toggle LED state
     digitalWrite(LED_PIN,ledState); // Apply new LED state
   }
}
```
