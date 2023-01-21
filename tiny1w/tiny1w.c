/* tiny1w-optimized.c - 1-wire protocol
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
#include "tiny1w.h"

/* t1w_busreset() - resets the 1-wire bus
 *
 * Entry conditions
 *	- pin is INPUT/LOW
 *	- bus is idle
 *
 * Parameters:
 *	d_mask = mask value for the 1-wire pin
*/
s8_t t1w_busreset(u8_t d_mask)
{
	u8_t d_high = T1W_DDR;
	u8_t d_low = d_high | d_mask;
	u8_t t;

	/* Set pin to output/low for 480 us
	*/
	T1W_DDR = d_low;
	T1W_DELAYus(480);
	T1W_DDR = d_high;

	/* Wait 5 us.
	*/
	T1W_DELAYus(5);

	/* Sample the input until it goes low. Input should be low from 60..120 if device is present.
	*/
#if T1W_PRESENCE
	t = 0;
	for (;;)
	{
		if ( (T1W_PINR & d_mask) == 0 )
			break;
		if ( ++t > 30 )
			return T1W_RST_NOTPRESENT;
	}

	/* Wait until pin goes high again (longer than max: error)
	*/
	for (;;)
	{
		if ( (T1W_PINR & d_mask) != 0 )
			break;
		if ( ++t > 60 )
			return T1W_RST_NOTGONE;
	}
	while ( t < 120 )
	{
		T1W_DELAYus(5);
		t++;
	}
#else
	T1W_DELAYus(120);
#endif

	return T1W_OK;
}

/* t1w_writebyte() - write a byte to the 1-wire bus
*/
void t1w_writebyte(u8_t d_mask, u8_t data)
{
	u8_t d_high = T1W_DDR;
	u8_t d_low = d_high | d_mask;

	for ( u8_t i = 0; i < 8; i++ )
	{
		if ( (data & 1) == 0 )
		{
			T1W_DDR = d_low;		/* Output low for 65 us */
			T1W_DELAYus(65);
			T1W_DDR = d_high;
			T1W_DELAYus(55);
		}
		else
		{
			T1W_DDR = d_low;		/* Output low for 1 us */
			T1W_DELAYus(1);
			T1W_DDR = d_high;
			T1W_DELAYus(120);
		}
		data = data >> 1;
	}
}

/* t1w_readbyte() - read a byte from the onw-wire bus
*/
u8_t t1w_readbyte(u8_t d_mask)
{
	u8_t d_high = T1W_DDR;
	u8_t d_low = d_high | d_mask;
	u8_t v = 0;

	/* LSB first
	*/
	for ( u8_t i = 0; i < 8; i++ )
	{
		T1W_DDR = d_low;		/* Output low for 1 us */
		T1W_DELAYus(1);
		T1W_DDR = d_high;

		T1W_DELAYus(15);
		v = v >> 1;
		if ( (T1W_PINR & d_mask) != 0 )
		{
			v = v | 0x80;
		}
		T1W_DELAYus(45);
	}
	return v;
}
