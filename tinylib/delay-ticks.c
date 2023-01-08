/* delay_ticks.c - delay_ticks()
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

#if PASSIVE_TIME

void delay_ticks(u32_t ticks)
{
	u8_t then;
	u8_t now;
	u32_t elapsed = 0;

	then = TCNT0;

	do {
		now = TCNT0;
		elapsed += (u32_t)(u8_t)(now - then);	/* Cast to u8_t forces overflow */
		then = now;
	} while ( elapsed < ticks );
}

#else

void delay_ticks(u32_t ticks)
{
	u32_t then;
	u32_t now;
	u32_t elapsed = 0;

	then = read_time_32();

	do {
		now = read_time_32();
		elapsed += now - then;
		then = now;
	} while ( elapsed < ticks );
}

#endif
