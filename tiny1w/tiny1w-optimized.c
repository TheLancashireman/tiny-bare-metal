/* tiny1w-optimized.c - 1-wire protocol
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
#include "tiny1w.h"

#define DELAYus(us) \
do {								\
	for ( t = 0; t < us/2; t++ )	\
	{								\
		asm("nop");					\
	}								\
} while (0)

/* w1_busreset() - resets the 1-wire bus
 *
 * Entry conditions
 *	- pin is INPUT/LOW
 *	- bus is idle
 *
 * Parameters:
 *	d_mask = mask value for the 1-wire pin
*/
s8_t w1_busreset(u8_t d_mask)
{
	u8_t d_high = DDRB;
	u8_t d_low = d_high | d_mask;
	u8_t t;

	/* Set pin to output/low for 480 us
	*/
	DDRB = d_low;
	DELAYus(480);
	DDRB = d_high;

	/* Wait 5 us.
	*/
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	/* Sample the input until it goes low. Input should be low from 60..120 if device is present.
	*/
#if W1_PRESENCE
	t = 0;
	for (;;)
	{
		if ( (PINB & d_mask) == 0 )
			break;
		if ( ++t > 30 )
			return W1_RST_NOTPRESENT;
	}

	/* Wait until pin goes high again (longer than max: error)
	*/
	for (;;)
	{
		if ( (PINB & d_mask) != 0 )
			break;
		if ( ++t > 60 )
			return W1_RST_NOTGONE;
	}
#else
	DELAYus(120);
#endif

	return W1_OK;
}

/* w1_writebyte() - write a byte to the 1-wire bus
*/
void w1_writebyte(u8_t d_mask, u8_t data)
{
	u8_t d_high = DDRB;
	u8_t d_low = d_high | d_mask;

	for ( u8_t i = 0; i < 8; i++ )
	{
		if ( (data & 1) == 0 )
		{
			DDRB = d_low;		/* Output low for 65 us */
			DELAYus(65);
			DDRB = d_high;
			DELAYus(55);
		}
		else
		{
			DDRB = d_low;		/* Output low for 1 us */
			asm("nop");
			DDRB = d_high;
			DELAYus(120);
		}
	}
}

/* w1_readbyte() - read a byte from the onw-wire bus
*/
u8_t w1_readbyte(u8_t d_mask)
{
	u8_t d_high = DDRB;
	u8_t d_low = d_high | d_mask;
	u8_t v = 0;

	/* LSB first
	*/
	for ( u8_t i = 0; i < 8; i++ )
	{
		DDRB = d_low;		/* Output low for 1 us */
		asm("nop");
		DDRB = d_high;

		DELAYus(15)l
		v = v >> 1;
		if ( (PINB & d_mask) != 0 )
		{
			v = v | 0x80;
		}
	}
	return v;
}
