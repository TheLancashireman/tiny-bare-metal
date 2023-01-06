/* w1.c - 1-wire protocol
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
#include "w1.h"

/* w1_reset() - resets the 1-wire bus
*/
s8_t w1_reset(u8_t pin)
{
	/* Set pin to low/input
	*/
	pin_set(pin, LOW);
	pin_mode(pin, INPUT);

	/* Ensure pin is high, i.e. no slaves occupying the bus.
	 * Wait longer than max --> error
	*/
	for ( s8_t i = 0; i < W1_TRSTH; i++ )
	{
		w1_delay(1);
		if ( pin_get(pin) )
			break;
	}

	if ( !pin_get(pin) )
		return W1_RST_NOTIDLE;
	
	/* Set pin to output - drives low - for 480 us
	*/
	pin_mode(pin, OUTPUT);
	w1_delay(480);
	pin_mode(pin, INPUT);

	/* Wait 80 us then sample the input. Input should be low from 60..120 if device is present.
	*/
	w1_delay(80);
	if ( pin_get(pin) )
		return W1_RST_NOTPRESENT;

	/* Wait until pin goes high again (longer than max: error)
	*/
	for ( s8_t i = 0; i < 240; i++ )
	{
		w1_delay(1);
		if ( pin_get(pin) )
			break;
	}

	if ( !pin_get(pin) )
		return W1_RST_NOTGONE;

	return W1_OK;
}

/* w1_write0() - write a '0' bit on the 1-wire bus
 *
 * Assumption: pin is LOW/INPUT on entry
 *
 * Slave samples line at time 15us < t < 60us after falling edge
 * ==> Master must hold low for at least 60 us ... max 120us
 * We choose 65us
*/
static inline void w1_write0(u8_t pin)
{
	/* Force output pin to low for 60us < t < 120us
	*/
	pin_mode(pin, OUTPUT);
	w1_delay(65);

	/* Back to high-impedance for 1 us
	*/
	pin_mode(pin, INPUT);
	w1_delay(1);
}

/* w1_write1() - write a '1' bit on the 1-wire bus
 *
 * Assumption: pin is LOW/INPUT on entry
 *
 * Slave samples line at time 15us < t < 60us after falling edge
 * ==> Master releases after 1us, must allow 60 us
 * We choose 65 us
*/
static inline void w1_write1(u8_t pin)
{
	/* Force output pin to low for 1us
	*/
	pin_mode(pin, OUTPUT);
	w1_delay(1);

	/* Back to high-impedance for 65 us
	*/
	pin_mode(pin, INPUT);
	w1_delay(65);
}

/* w1_write_byte() - write a byte to the 1-wire bus
*/
void w1_write_byte(u8_t pin, u8_t b)
{
	s8_t i;
	for ( i = 0; i < 8; i++ )
	{
		if ( (b & 0x01) == 0 )
			w1_write0(pin);
		else
			w1_write1(pin);
		b = b >> 1;
	}
}

/* w1_readbyte() - read a byte from the onw-wire bus
*/
u8_t w1_readbyte(u8_t pin)
{
	/* LSB first
	*/
	u8_t v = 0;
	for ( u8_t i = 0; i < 8; i++ )
	{
		v = v >> 1;
		if ( w1_read(pin) != 0 )
			v = v | 0x80;
	}
	return v;
}
