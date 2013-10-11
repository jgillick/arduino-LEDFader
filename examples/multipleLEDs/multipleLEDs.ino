#include <LEDFader.h>

/*
  Fades 6 LEDs, all to random PWM values and durations.
  This uses all the PWM pins on the UNO board.

  Circuit
  -------
   * Connect the anode (flat side/long leg) of each LED to one of the PWM pins listed below on the arduino, via a 220 ohm resistor.
   * Connect the cathode (short leg) of each LED to ground.

   * PWM Pins on the UNO board:
      - 3
      - 5
      - 6
      - 9
      - 10
      - 11

  RGB LEDs
  --------
  You can also use this code with 2 RGB LEDs. This will fade each of the colors on an off at
  random durations and intensities. Check the LED datasheet to see if it's a common cathode or anode and
  which legs are which.

  For common anode RGB LEDs, attach the anode to ground and each cathode leg to a PWM pin through a
  resistor.

  For common cathode RGB LEDs, the cathode will be connected straight to 5+ and each
  of the anode legs will be connected to a PWM pin through a resistor. Since you're basically attaching
  the ground pins to the arduino, the brightness values are reversed: 0 is 100% and 255 is completely off.
  This is called current sinking.
*/


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
        led->fade(color, duration);
      }
      // Down
      else {
        led->fade(0, duration);
      }
    }
  }
}