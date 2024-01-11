# Bounce2

Debouncing library for Arduino and Wiring by Thomas Ouellet Fredericks and many [contributors](https://github.com/thomasfredericks/Bounce2/graphs/contributors).

The mechanical part of buttons and switches vibrate slightly when closed or opened causing multiple undesired false states (similar to noise). This library filters out these undesired state changes. You can learn more about debouncing here: 
* [John Errington's Experiments with an Arduino - Using digital inputs: Switch bounce and solutions to it](http://www.skillbank.co.uk/arduino/switchbounce.htm)
* [Wikipedia article on contact Debouncing](http://en.wikipedia.org/wiki/Debounce#Contact_bounce)

The library is composed of three classes:
* `Bounce2::Button` : The class that most people will use. It is the most feature rich class for deboucing hardware buttons. 
* `Debouncer` : The code that does the actual debouncing. Only advanced users should use this class for creating their own implememtations.
* `Bounce` : This class links the `Debouncer` class to a hardware pin on your board. It is odly named because it needs to be backward compatible to previous versions of this library.

# Need Help?

Please post your usage questions on the [Arduino Forums](https://forum.arduino.cc/latest).

# Installation

Install through your software's Library Manager or download the latest version [here](https://github.com/thomasfredericks/Bounce2/archive/master.zip) and put the "Bounce2" folder in your "libraries" folder. 

Please note that the original version of this library (Bounce 1) is included in the "extras" folder of the download but not supported anymore.

# Basic Use

## Global Space

```cpp
#include <Bounce2.h> 
Bounce2::Button button = Bounce2::Button(); // INSTANTIATE A Bounce2::Button OBJECT
```

## Configuration in `setup()`

In the code sample below :
* Change *PIN* to the hardware pin of the button. 
* Change *PIN_MODE* to `INPUT_PULLUP` if using an internal pullup, or `INPUT` if using an external pullup. 
* Change *INTERVAL_IN_MS* to the debounce interval in millisecons. `5` is a good value.
* Change *PRESSED_STATE* to `LOW` if the button outputs a `LOW` when pressed, or to `HIGH` if the button outputs a `HIGH` when pressed.  

```cpp
button.attach ( PIN , PIN_MODE );
button.interval( INTERVAL_IN_MS );
button.setPressedState( PRESSED_STATE ); 
```


## Use in `loop()`

```cpp
// UPDATE THE BUTTON BY CALLING .update() AT THE BEGINNING OF THE LOOP:
button.update();

// IF THE BUTTON WAS PRESSED THIS LOOP:
if ( button.pressed() ) {
    // DO SOMETHING IF THE BUTTON WAS PRESSED THIS LOOP...
}
```

# Examples

## A Button Toggling a LED

```cpp
/* 
 DESCRIPTION
 ====================
 This is an example of the Bounce2::Button class. 
 When the user presses a physical button, it toggles a LED on or off.
 The Button class matches an electrical state to a physical action. 
 Use .setPressedState(LOW or HIGH) to set the detection state for when the button is pressed.

 INSTRUCTIONS
 ====================
 Set BUTTON_PIN to the pin attached to the button.
 Set LED_PIN to the pin attached to a LED.
 
 */
 
// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

// INSTANTIATE A Button OBJECT
Bounce2::Button button = Bounce2::Button();

// WE WILL attach() THE BUTTON TO THE FOLLOWING PIN IN setup()
#define BUTTON_PIN 39 

// DEFINE THE PIN FOR THE LED :
// 1) SOME BOARDS HAVE A DEFAULT LED (LED_BUILTIN)
//#define LED_PIN LED_BUILTIN
// 2) OTHERWISE SET YOUR OWN PIN
#define LED_PIN 13

// SET A VARIABLE TO STORE THE LED STATE
bool ledState = LOW;

void setup() {

  // BUTTON SETUP 
  
  // SELECT ONE OF THE FOLLOWING :
  // 1) IF YOUR BUTTON HAS AN INTERNAL PULL-UP
  // button.attach( BUTTON_PIN ,  INPUT_PULLUP ); // USE INTERNAL PULL-UP
  // 2) IF YOUR BUTTON USES AN EXTERNAL PULL-UP
  button.attach( BUTTON_PIN, INPUT ); // USE EXTERNAL PULL-UP

  // DEBOUNCE INTERVAL IN MILLISECONDS
  button.interval(5); 

  // INDICATE THAT THE LOW STATE CORRESPONDS TO PHYSICALLY PRESSING THE BUTTON
  button.setPressedState(LOW); 
  
  // LED SETUP
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,ledState);

}

void loop() {
  // UPDATE THE BUTTON
  // YOU MUST CALL THIS EVERY LOOP
  button.update();

  if ( button.pressed() ) {
    
    // TOGGLE THE LED STATE : 
    ledState = !ledState; // SET ledState TO THE OPPOSITE OF ledState
    digitalWrite(LED_PIN,ledState);

  }
}
```

## More Examples

You can find more examples in the **examples** folder. 

# Documentation

## Bounce2::Button

The `Bounce2::Button` class extends `Bounce` and adds  `pressed()` and `released()` methods. It is the most feature rich class of the library.

| Method | Description |
| --------------- | --------------- |
|   `Button()` | Create an instance of the Button class. By default, the pressed state is matched to a HIGH electrical level. |
| `void`  `update()` | Updates the pin's state. Because Bounce does not use interrupts, you have to "update" the object before reading its value and it has to be done as often as possible (that means to include it in your `loop()`). Only call `update()` for each Bounce instance once per `loop()`. |
| `void`  `setPressedState(bool state)` | Set the electrical state (HIGH/LOW) that corresponds to a physical press. By default, the pressed state is matched to a HIGH electrical level. |
| `bool`  `getPressedState()` | Get the electrical state (HIGH/LOW) that corresponds to a physical press. |
| `bool `  `isPressed() ` | Returns true if the button **is** currently pressed. |
| `bool `  `pressed()` | Returns true if the button **was** pressed |
| `bool `  `released()` | Returns true if the button **was** released |
| `void`  `attach(int pin, int mode)` | Attach to a pin and sets that pin's mode (INPUT, INPUT_PULLUP or OUTPUT). |
| `int`  `getPin()` | Return pin that this instance is attached to.  |
| `void`  `interval ( uint16_t  interval_millis )` | Sets the debounce interval in milliseconds. |
| `unsigned long`  `previousDuration()` | Returns the duration in milliseconds of the previous state. |
| `unsigned long`  `currentDuration()` | Returns the duration in milliseconds of the current state. Is reset to 0 when the state changes.  |
| `bool`  `changed()` | Returns true if the state changed on last update. |
| `bool`  `read()` | Returns the pin's state (HIGH or LOW). |
| `bool`  `fell()` | Returns true if pin signal transitions from high to low since the last update. |
| `bool`  `rose()` | Returns true if pin signal transitions from low to high since the last update. |


## Bounce

The `Bounce` class extends `Debouncer` and links it to a hardware pin. This class is odly named, but it will be kept that so it stays compatible with previous code.

| Method | Description |
| --------------- | --------------- |
|   `Bounce()` | Create an instance of the Bounce class. |
| `void`  `update()` | Updates the pin's state. Because Bounce does not use interrupts, you have to "update" the object before reading its value and it has to be done as often as possible (that means to include it in your `loop()`). Only call `update()` for each Bounce instance once per `loop()`. |
| `void`  `attach(int pin, int mode)` | Attach to a pin and sets that pin's mode (INPUT, INPUT_PULLUP or OUTPUT). |
| `int`  `getPin()` | Return pin that this instance is attached to.  |
| `void`  `interval ( uint16_t  interval_millis )` | Sets the debounce interval in milliseconds. |
| `unsigned long`  `previousDuration()` | Returns the duration in milliseconds of the previous state. |
| `unsigned long`  `currentDuration()` | Returns the duration in milliseconds of the current state. Is reset to 0 when the state changes.  |
| `bool`  `changed()` | Returns true if the state changed on last update. |
| `bool`  `read()` | Returns the pin's state (HIGH or LOW). |
| `bool`  `fell()` | Returns true if pin signal transitions from high to low since the last update. |
| `bool`  `rose()` | Returns true if pin signal transitions from low to high since the last update. |

## Debouncer

The `Debouncer` class. Just the debouncing code separated from all hardware.

| Method | Description |
| --------------- | --------------- |
| `Debouncer()` | Create an instance of the Debouncer class.|
| `void`  `update()` | Updates the pin's state. Because Bounce does not use interrupts, you have to "update" the object before reading its value and it has to be done as often as possible (that means to include it in your `loop()`). Only call `update()` for each Bounce instance once per `loop()`. |
| `void`  `interval ( uint16_t  interval_millis )` | Sets the debounce interval in milliseconds. |
| `unsigned long`  `previousDuration()` | Returns the duration in milliseconds of the previous state. |
| `unsigned long`  `currentDuration()` | Returns the duration in milliseconds of the current state. Is reset to 0 when the state changes.  |
| `bool`  `changed()` | Returns true if the state changed on last update. |
| `bool`  `read()` | Returns the pin's state (HIGH or LOW). |
| `bool`  `fell()` | Returns true if pin signal transitions from high to low since the last update. |
| `bool`  `rose()` | Returns true if pin signal transitions from low to high since the last update. |


# Alternate Algorithms

The following alternate debouncing algorithms are for **advanced** users or specific cases.

## Stable Interval

By default, the Bounce library uses a stable interval to process the debouncing. This is simpler to understand and can cancel unwanted noise.

![](https://raw.github.com/thomasfredericks/Bounce-Arduino-Wiring/master/extras/BouncySwitch_stable.png)

## Lock-out Interval

By defining "#define BOUNCE_LOCK_OUT" in "Bounce.h" you can activate an alternative debouncing method. This method is a lot more responsive, but does not cancel noise.

```
#define BOUNCE_LOCK_OUT
```

![](https://raw.github.com/thomasfredericks/Bounce-Arduino-Wiring/master/extras/BouncySwitch_lockout.png)

## Prompt Detection

By defining "#define BOUNCE_WITH_PROMPT_DETECTION" in "Bounce.h" you can activate an alternative debouncing method. Button state changes are available immediately so long as the previous state has been stable for the timeout period. Otherwise the state will be updated as soon as  the timeout period allows.

* Able to report acurate switch time normally with no delay.
* Use when accurate switch transition timing is important.

```
#define BOUNCE_WITH_PROMPT_DETECTION
```


