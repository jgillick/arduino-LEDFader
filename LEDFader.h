/*
 * LED.h
 *
 *  Created on: Sep 24, 2013
 *      Author: jeremy
 */

#include "Arduino.h"

#ifndef LEDFader_H_
#define LEDFader_H_

// The minimum time (milliseconds) the program will wait between LED adjustments
// adjust this to modify performance.
#define MIN_INTERVAL 20

class LEDFader {
  uint8_t pin;
  unsigned long last_step_time;
  unsigned int interval;
  uint8_t color;
  uint8_t to_color;
  unsigned int duration;
  float percent_done;

  public:

    // Create a new LED Fader for a pin
    LEDFader(uint8_t pwm_pin=0);

    // Set the PWM pin that the LED is connected to
    void set_pin(uint8_t pwm_pin);
    uint8_t get_pin();

    // Set an LED to an absolute PWM value
    void set_value(int pwm);

    // Get the current LED PWM value
    uint8_t get_value();

    // Fade an LED to a PWM value over a duration of time (milliseconds)
    void fade(uint8_t pwm, unsigned int time);

    // Returns TRUE if there is an active fade process
    bool is_fading();

    // Stop the current fade where it's at
    void stop_fade();

    // Update the LEDs along the fade
    // Returns TRUE if a fade is still in process
    bool update();

    // Decrease the current fading speed by a number of milliseconds
    void slower(int by_seconds);

    // Increase the current fading speed by a number of milliseconds
    void faster(int by_seconds);

    // Returns how much of the fade is complete in a percentage between 0 - 100
    uint8_t get_progress();
};

#endif /* LEDFader_H_ */
