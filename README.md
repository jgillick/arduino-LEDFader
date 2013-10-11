Background LED Fading Library for Arduino
========================================

This arduino library can fade individual LEDs in the background without blocking your main program.

Instead of using a for loop and `delay` to fade an LED from one PWM value to another -- which will block all other processes -- this will check the time each loop cycle to see if the value should be adjusted.

For example, to fade from 0 - 200 in 1 second, it would increment the PWM value by 1 every 50 milliseconds -- without stopping your program while it waits. There are also other optimizations to make the animations smooth and accurate without eating too many chip resources.

Install
-------
Move the arduino-LEDFader folder into the [arduino library directory](http://arduino.cc/en/Guide/Libraries) and rename it from `arduino-LEDFader` to `LEDFader`.

Then in your sketch you just need to add this to the top of your file:

```cpp
#include <LEDFader.h>
```


Simple Examples
---------------

Fade an LED on pin 3 up in 3 seconds.

```cpp
#include <LEDFader.h>

// Create new LED Fader on pin 3
LEDFader led = LEDFader(3);

void setup() {
  // Fade from 0 - 255 in 3 seconds
  led.fade(255, 3000);
}

void loop() {
  // Need to call update each loop cycle to adjust the PWM if needed
  led.update();
}
```

Building on that example, we can alternate by fading up and down

```cpp
#include <LEDFader.h>

// Create new LED Fader on pin 3
LEDFader led = LEDFader(3);

void setup() {
  led.fade(255, 3000);
}

void loop() {
  led.update();

  if (led.is_fading() == false) {

    // Fade from 255 - 0
    if (led.get_value() == 255) {
      led.fade(0, 3000);
    }
    // Fade from 0 - 255
    else {
      led.fade(255, 3000);
    }
  }
}
```


Multiple LEDs or RGB
---------------------

This example will fade 6 LEDs, all to random PWM values and durations. You could, instead, replace 6 LEDs with 2 RGB LEDs.

```cpp
#include <LEDFader.h>

#define LED_NUM 6

// 6 LEDs (perhaps 2 RGB LEDs)
LEDFader leds[LED_NUM] = {
  LEDFader(3),
  LEDFader(5),
  LEDFader(6),
  LEDFader(9),
  LEDFader(10),
  LEDFader(11)
};

void setup() {
}

void loop() {

  // Update all LEDs and start new fades if any are done
  for (byte i = 0; i < LED_NUM; i++) {
    LEDFader *led = &leds[i];
    led->update();

    // Set new fade
    if (led->is_fading() == false) {
      int duration = random(1000, 3000); // between 1 - 3 seconds

      // Up
      if (led->get_value() == 0) {
        byte color = random(100, 255);
        led.fade(color, duration);
      }
      // Down
      else {
        led.fade(0, duration);
      }
    }
  }
}
```




