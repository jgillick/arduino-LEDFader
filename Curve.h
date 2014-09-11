/* 
 * File:   Curve.h
 * Author: cameron
 *
 * Created on October 22, 2013, 1:07 AM
 */

#ifndef CURVE_H
#define	CURVE_H

#include <avr/pgmspace.h>

class Curve {
 static const uint8_t etable[] PROGMEM;
public:
 static uint8_t exponential(uint8_t);
 static uint8_t linear(uint8_t);
 static uint8_t reverse(uint8_t);
};

#endif	/* CURVE_H */

