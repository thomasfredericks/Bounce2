# BOUNCE 2

Debouncing library for Arduino and Wiring by Thomas Ouellet Fredericks with contributions from: Eric Lowry, Jim Schimpf, Tom Harkaway and Joachim Krüger.

More about debouncing: http://en.wikipedia.org/wiki/Debounce#Contact_bounce


# HAVE A QUESTION?

Please post your questions here
http://forum.arduino.cc/index.php?topic=266132.0

# INSTALLATION & DOWNLOAD

Install through your software's Library Manager or download the latest version [here](https://github.com/thomasfredericks/Bounce2/archive/master.zip) and put the "Bounce2" folder in your "libraries" folder. 

The original version of Bounce (Bounce 1) is included in the download but not supported anymore.

# DOCUMENTATION

The complet documentation can be found in the "docs" folder or [online here](http://thomasfredericks.github.io/Bounce2/).

# DEBOUNCE ALGORITHMS 


## Stable interval

By default, the Bounce library uses a stable interval to process the debouncing. This is simpler to understand and can cancel unwanted noise.

![](https://raw.github.com/thomasfredericks/Bounce-Arduino-Wiring/master/extras/BouncySwitch_stable.png)

## Lock-out interval

By defining "#define BOUNCE_LOCK_OUT" in "Bounce.h" you can activate the alternative debouncing method. This method is a lot more responsive, but does not cancel noise.

![](https://raw.github.com/thomasfredericks/Bounce-Arduino-Wiring/master/extras/BouncySwitch_lockout.png)


