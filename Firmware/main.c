/*
 * Controller code for a device that reads analog sensor values and sleeps
 * while it isn't used. Check the README at Github for more information.
 *
 * Written by Gregor Ottmann, https://github.com/Zappes
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#include "config.h"
#include "motion.h"
#include "timer.h"

void init() {
	DDR &= ~_BV(PIN_LIGHT | PIN_MOVE);
}

int main(void)
{
	// disable interrupt
	cli();

	init();
	timer_init();
	motion_init();

	// enable interrupt
	sei();

	while(1)
	{
	}

	return 0;
}

