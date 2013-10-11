#include <LEDFader.h>

/*
  Fades a single LED up and down using LED Fader.
  Connect an LED to pin 3
*/

#define LED_PIN 3

#define FADE_TIME 2000

#define DIR_UP 1
#define DIR_DOWN -1

LEDFader led;
int direction = DIR_UP;

void setup() {
  led = LEDFader(LED_PIN);
  led.fade(255, FADE_TIME);
}

void loop() {
  led.update();

  // LED no longer fading, switch direction
  if (!led.is_fading()) {

    // Fade down
    if (direction == DIR_UP) {
      led.fade(0, FADE_TIME);
      direction = DIR_DOWN;
    }
    // Fade up
    else {
      led.fade(255, FADE_TIME);
      direction = DIR_UP;
    }
  }
}