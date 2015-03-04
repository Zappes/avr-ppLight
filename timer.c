/*
 * timer.c
 *
 *  Created on: 04.03.2015
 *      Author: zaphod
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "config.h"
#include "timer.h"

volatile uint16_t delay = TIMER_DELAY;

#define DIR_NONE	0
#define DIR_DOWN	1
#define DIR_UP		2

volatile uint8_t brightness = 0;
volatile uint8_t direction = DIR_NONE;

void timer_init() {
	// enable output for the strip
	DDR |= _BV(PIN_STRIP);

	// output PWM on OC0B/PB1, Fast PWM
	TCCR0A |= _BV(COM0B1) | _BV(WGM00) | _BV(WGM01);

	// prescaler set to 256, giving a frequency of 32khz for the counter and a pwm freq of 122hz
	TCCR0B |= _BV(CS02);

	// enable interrupt on overflow
	TIMSK |= _BV(TOIE0);

	// strip off
	OCR0B = 0;
}

void timer_start() {
	cli();
	delay = TIMER_DELAY;
	direction = DIR_UP;
	sei();
}

ISR(TIMER0_OVF_vect) {
	if (delay == 0) {
		if(PIN & _BV(PIN_MOVE)) {
			// if the delay ran out but the PIR is still high, we keep the lights on for a bit longer.
			// this is needed because the PIR just keeps a high level instead of sending pulses if
			// movement keeps occurring.
			delay = 10;
		}
		else {
			direction = DIR_DOWN;
		}
	} else {
		delay--;
	}

	if (direction == DIR_UP && brightness < 0xFF) {
		brightness++;

		if (brightness == 1) {
			// enable output for the strip
			DDR |= _BV(PIN_STRIP);
		}
	} else if (direction == DIR_DOWN && brightness > 0x00) {
		brightness--;

		if (brightness == 0) {
			// disable output for the strip
			DDR &= ~_BV(PIN_STRIP);
		}
	}

	OCR0B = brightness;
}
