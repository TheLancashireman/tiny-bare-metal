/* async.h - header file for tinylib's async serial functions
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
#ifndef ASYNC_H
#define ASYNC_H	1

#include "tinylib.h"

#if ASYNC_BITRATE != 0

#if ASYNC_BITRATE == 9600
#define BIT_TIME	(104/T0_RESOLUTION)
#elif ASYNC_BITRATE == 4800
#define BIT_TIME	(208/T0_RESOLUTION)
#else
#error "Unsipported bit rate"
#endif

static inline u8_t bit_delay(u8_t t0)
{
	u8_t t;
	do {
		t = TCNT0;
	} while ( (t - t0) < BIT_TIME );
	return t;
}

#endif

#endif
