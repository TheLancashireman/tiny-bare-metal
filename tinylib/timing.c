/* timing.c - timing_init() and timer overflow interrupt
 *
 * (c) David Haworth
 *
 *  This file is part of tiny-bare-metal.
 *
 *  tiny-bare-metal is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  tiny-bare-metal is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with tiny-bare-metal.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "tinylib.h"
#include <avr/interrupt.h>

/* High-order time bits.
*/
volatile u64_t time_high;

/* timing_init() - initialise the timing using Timer0
 *
 * Erases all output-compare and input-capture settings, so call this function
 * first, before initialising any PWM or pulse-width measurement functionality.
 *
 * Timer0 runs at a maximum of 1 MHz when used for timing.
*/
void timing_init(void)
{
	u8_t s = disable();
	TCCR0A = 0x00;						// Clear all output-compare modes
	TCCR0B = T0_CLKSEL;					// Select CLKIO/64 as clock source
	TCNT0 = 0x00;						// Clear the counter
	OCR0A = 0x00;						// Clear both output-compare registers
	OCR0B = 0x00;
	TIMSK = (TIMSK & 0x18) | 0x02;		// Disable Timer0 output-compare interrupts; enable overflow interrupt
	TIFR = 0x1a;						// Clear all pending interrupts for Timer0
	(void)restore(s);
}

ISR(TIM0_OVF_vect)
{
	time_high += 0x100;
}
