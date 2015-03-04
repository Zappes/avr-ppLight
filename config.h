#include <avr/io.h>

#define PORT	PORTB
#define PIN		PINB
#define DDR		DDRB

#define PIN_MOVE	PB0
#define PIN_STRIP	PB1

#define PIN_LIGHT	PB3
#define PIN_TRIM	PB4
#define ADC_LIGHT	3
#define ADC_TRIM	2

// the time the light stays on after the last motion detection.
// expressed in timer ticks which have a freq of 122hz, i.e. use 122 for 1 second.
// should be at least 3 seconds because of the re-arming delay of the PIR
#define TIMER_DELAY 366
