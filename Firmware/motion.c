/*
 * motion.c
 *
 *  Created on: 04.03.2015
 *      Author: zaphod
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "config.h"
#include "motion.h"
#include "timer.h"
#include "adc.h"

void motion_init() {
	GIMSK = _BV(PCIE);
	PCMSK = _BV(PCINT0);
}

ISR(PCINT0_vect) {
	// only trigger on high level!
	if(PIN & _BV(PIN_MOVE)) {
		if(adc_read_byte(ADC_TRIM) <= adc_read_byte(ADC_LIGHT)) {
			timer_start();
		}
	}
}
