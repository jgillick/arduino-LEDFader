/*
 * LED.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: jeremy
 */

#include "LEDFader.h"

LEDFader::LEDFader(uint8_t pwm_pin) {
  pin = pwm_pin;
  color = 0;
  to_color = 0;
  last_step_time = 0;
  interval = 0;
  duration = 0;
  percent_done = 0;
}

void LEDFader::set_value(int value) {
  color = (byte)constrain(value, 0, 255);
  analogWrite(pin, color);
}

uint8_t LEDFader::get_value() {
  return color;
}

void LEDFader::slower(int by) {
  float cached_percent = percent_done;
  duration += by;
  fade(to_color, duration);
  percent_done = cached_percent;
}

void LEDFader::faster(int by) {
  float cached_percent = percent_done;

  // Ends the fade
  if (duration <= by) {
    stop_fade();
    set_value(to_color);
  }
  else {
    duration -= by;
    fade(to_color, duration);
  }
  percent_done = cached_percent;
}

void LEDFader::fade(uint8_t value, unsigned int time) {
  stop_fade();
  percent_done = 0;

  // Color hasn't changed
  if (value == color) {
    return;
  }

  if (time <= MIN_INTERVAL) {
    set_value(value);
    return;
  }

  duration = time;
  to_color = (byte)constrain(value, 0, 255);

  // Figure out what the interval should be so that we're chaning the color by at least 1 each cycle
  // (minimum interval is MIN_INTERVAL)
  float color_diff = abs(color - to_color);
  interval = round((float)duration / color_diff);
  if (interval < MIN_INTERVAL) {
    interval = MIN_INTERVAL;
  }

  last_step_time = millis();
}

bool LEDFader::is_fading() {
  if (duration > 0)
    return true;
  return false;
}

void LEDFader::stop_fade() {
  percent_done = 100;
  duration = 0;
}

uint8_t LEDFader::get_progress() {
  return round(percent_done);
}

bool LEDFader::update() {
  // No fade
  if (duration == 0) {
    return false;
  }

  unsigned long now = millis();
  unsigned int time_diff = now - last_step_time;

  // Interval hasn't passed yet
  if (time_diff < interval) {
    return true;
  }

  // How far along have we gone since last update
  float percent = (float)time_diff / (float)duration;
  percent_done += percent;

  // We've hit 100%, set LED to the final color
  if (percent >= 1) {
    stop_fade();
    set_value(to_color);
    return false;
  }

  // Move color to where it should be
  int color_diff = to_color - color;
  int increment = round(color_diff * percent);

  set_value(color + increment);

  // Update time and finish
  duration -= time_diff;
  last_step_time = millis();
  return true;
}
