/* sleep.c - low-power sleep
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

#ifndef TIMSK0
#define TIMSK0	TIMSK
#endif
#ifndef TIFR0
#define TIFR0	TIFR
#endif

/* sleep() - sleep for a given number of intervals.
 *
 * An interval is an overflow of TCNT0 with the prescaler set to max (1024)
 *
 * The duration of an interval is equal to 1024*256/HZ seconds.
*/
void sleep(u8_t n_intervals)
{
	/* Disable interrupts and record the previous state.
	*/
	u8_t s = TL_disable();

	/* Save the timer settings
	*/
	u8_t tccr0a = TCCR0A;
	u8_t tccr0b = TCCR0B;
	u8_t timsk0 = TIMSK0;

	/* Set up the timer for slowest overflow interrupt
	*/
	GTCCR = 0x81;			// Stop the prescaler
	TCCR0A = 0x00;			// Clear all output-compare modes
	TCCR0B = 0x05;			// Select clock source = clkio/1024
	TCNT0 = 0x00;			// Clear the counter
	TIMSK0 = (1<<TOIE0);	// Disable Timer0 output-compare interrupts; enable overflow interrupt
	TIFR0 = 0xff;			// Clear all pending interrupts for Timer0
	GTCCR = 0x01;			// Start and reset the prescaler
	MCUCR &= ~0x18;			// Set sleep mode to idle
	MCUCR |= 0x20;			// Enable sleep mode

	enable();
	while ( n_intervals > 0 )
	{
		asm("sleep");	// Sleep for the given number of intervals
		n_intervals--;
	}
	(void)disable();
	MCUCR &= ~0x20;		// Disable sleep mode

	/* Restore Timer 0 settings
	*/
	TCCR0A = tccr0a;
	TCCR0B = tccr0b;
	TIMSK0 = timsk0;

	/* Restore the previous interrupt state
	*/
	(void)TL_restore(s);
}
