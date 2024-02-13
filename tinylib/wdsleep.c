/* wdsleep.c - power-off sleep using watchdog timer
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

/* wdsleep() - sleep for a time give by the 2nd parameter
 *
 * The mode is given by the first parameter
 *
 * The time is given by the 2nd parameter, which contains bits WDP3..WDP0 of WDTCR:
 *		0x00	16ms	WDSLEEP_16ms
 *		0x01	32ms	WDSLEEP_32ms
 *		0x02	64ms	WDSLEEP_64ms
 *		...		each value being twice the previous
 *		0x06	1.0s	WDSLEEP_1s
 *		0x07	2.0s	WDSLEEP_2s
 *		0x20	4.0s	WDSLEEP_4s
 *		0x21	8.0s	WDSLEEP_8s
 *
 * The times are approximate, based on the 128kHz watchdog clock divided by 2**n (n = 11..20)
 * Note the offset position of the MSB
 *
 * Precondition: interrupts disabled
*/
void wdpsleep(u8_t sleep_mode, u8_t wdp_val)
{
	MCUSR = 0;						// Clear watchdog reset flag
	WDTCR = 0x18;					// Prime WDTCR for writing (WDCE | WDE)
	WDTCR = wdp_val | 0x50;			// WDCE=1, WDTIE=1, WDE=0 + wdp_val

	/* Clear out previous sleep mode; set sleep mode & enable.
	*/
	MCUCR = (MCUCR & ~MCUCR_SM) | (sleep_mode & MCUCR_SM) | MCUCR_SE;

	asm("sei");
	asm("sleep");		// Sleep till the watchdog times out
	asm("cli");

	MCUCR &= ~MCUCR_SE;	// Disable sleep mode
	WDTCR = 0x18;		// Prime WDTCR for writing (WDCE | WDE)
	WDTCR = 0x10;		// Clear everything out
}

/* wdsleep() - sleep for up to 255 seconds using watchdog timer
*/
void wdsleep(u8_t sleep_mode, u8_t secs)
{
	u8_t is = TL_disable();
	u8_t n8 = secs >> 3;

	while ( n8 > 0 )
	{
		wdpsleep(sleep_mode, WDSLEEP_8s);
		n8--;
	}

	if ( (secs & 4) != 0 )
	{
		wdpsleep(sleep_mode, WDSLEEP_4s);
	}

	if ( (secs & 2) != 0 )
	{
		wdpsleep(sleep_mode, WDSLEEP_2s);
	}

	if ( (secs & 1) != 0 )
	{
		wdpsleep(sleep_mode, WDSLEEP_1s);
	}

	TL_restore(is);
}

/* ISR(WDT_vect) - watchdog interrupt handler
*/
ISR(WDT_vect)
{
	/* Is there anything to do here? */
}
