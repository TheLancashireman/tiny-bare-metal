/* read-time-32.c - read_time_32()
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

#if !PASSIVE_TIME

u32_t read_time_32(void)
{
	u32_t h1;
	u32_t h2;
	u8_t l;

	h2 = time_low;

	do {
		h1 = h2;
		l = TCNT0;
		h2 = time_low;
	} while ( h1 != h2 );

	return h1 + l;
}

#endif
