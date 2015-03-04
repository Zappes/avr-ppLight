/*
 * adc.c
 *
 *  Created on: 04.03.2015
 *      Author: zaphod
 */
#include <avr/io.h>

#include "config.h"
#include "adc.h"

uint8_t adc_read_byte(uint8_t channel) {
	// left-adjust result, use vcc as ref voltage, select channel as provided
	ADMUX = _BV(ADLAR) | (channel & 0x0F);

	// enable ADC, set prescaler to 64
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);

	// start conversion
	ADCSRA |= (1 << ADSC);

	// wait for completion of conversion
	while (ADCSRA & (1 << ADSC) );

	// read result. we just use 8 bit resolution and have ADLAR set, so we only need ADCH
	uint8_t result = ADCH;

	// disable ADC (saves power)
	ADCSRA = 0;

	return result;
}
