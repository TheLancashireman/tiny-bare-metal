/* bit-delay.c - delay for one bit of serial data
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
#include "async.h"

#ifdef BIT_TIME

/* bit_delay() - delay for one bit time
 *
 * To avoid accumulating errors caused by the computation time of a bit,
 * the delay is measured from the end of the previous bit time.
 *
 * Example:
 *	t = bit_delay(TCNT0);
 *	<output 1st bit>
 *	t = bit_delay(t);
 *	<output 2nd bit>
 *	t = bit_delay(t);
 *	... and so on
*/
u8_t bit_delay(u8_t t0)
{
	u8_t t;
	do {
		t = TCNT0;
	} while ( ((u8_t)(t - t0)) < BIT_TIME );
	return t;
}

#endif
