/* tiny1w.h - 1-wire protocol
 *
 * (c) David Haworth
 *
 *  This file is part of one-wire.
 *
 *  one-wire is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  one-wire is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with one-wire.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef TINY1W_H
#define TINY1W_H	1

#include "tinylib.h"

/* Assume no debug trace if not specified
*/
#ifndef W1_DBG
#define W1_DBG	0
#endif

#if W1_DBG
#include "tinyio.h"
#define W1_PUTC(x)	putc(x)
#else
#define W1_PUTC(x)	do { } while (0)
#endif

/* Assume presence test if not specified
*/
#ifndef W1_PRESENCE
#define W1_PRESENCE	1
#endif

/* Maxim one-wire protocol (e.g. DS18B20)
 *
 * Communication always controlled by controller.
 * Bus is pulled to 0 by communication (open collector).
 * Pull-up of 5K0 (4K7) needed
 *
 * Reset pulse
 * - Controller pulls low for minimum 480 us, then release.
 * - Devices (if present) pull low within 60 us of release for min 60 us, max 240 us
 * - Controller must wait 480 us after release.
 *
 * Write (controller --> device)
 * - Controller pulls low
 * - Device samples line between 15 us and 60 us after falling edge. Therefore:
 * - To write 0, controller holds low for > 60 us (max 120 us)
 * - To write 1, controller releases after 1 us and waits for > 59 us
 *
 * Read (controller <-- device)
 * - Controller pulls low for 1 us
 * - Read 0: device holds low between 15 us and 60 us
 * - Read 1: device doesn't pull low
 * - Controller samples bus max 15 us after falling edge
 * - "Read slots must be min 60 us + 1 us recovery time" (why not stop when line goes high?)
*/

/* Return/status values
*/
#define W1_OK				0
#define W1_RST_NOTPRESENT	1
#define W1_RST_NOTIDLE		2
#define W1_RST_NOTGONE		3

/* Timing - see data sheet
*/
#define W1_TRSTL			480
#define W1_TRSTH			480
#define W1_TPDIH			60
#define W1_TPDLOW			240

#if HZ==1000000

/* W1_DELAYus() - delay for x us (calibrated for 1 MHz clock)
 *
 * The delay loop is calibrated assuming each iteration is 3 instructions == 3 us.
 * The loop always under-estimates; it is assumed that the extra us or two is provided
 * by nearby instructions.
*/
#define W1_DELAYus(us) \
do {								\
	u8_t tx = ((us))/3;				\
	for ( ; tx > 0 ; tx-- )			\
	{								\
		asm("nop");					\
	}								\
} while (0)

#else
#error "Delay function for other CPU frequencies to be implemented"
#endif

/* w1_readbit() - read a bit from the 1-wire bus
*/
static inline u8_t w1_readbit(u8_t d_mask)
{
	u8_t d_high = DDRB;
	u8_t d_low = d_high | d_mask;
	u8_t d = 0;

	DDRB = d_low;		/* Output low for 1 us */
	W1_DELAYus(1);
	DDRB = d_high;

	W1_DELAYus(15);
	if ( (PINB & d_mask) != 0 )
	{
		d = 1;
	}
	W1_DELAYus(45);
	return d;
}

extern s8_t w1_busreset(u8_t d_mask);
extern void w1_writebyte(u8_t d_mask, u8_t data);
extern u8_t w1_readbyte(u8_t d_mask);

#endif
