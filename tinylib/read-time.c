/* read-time.c - read_time()
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

#if TIME64
u64_t read_time(void)
{
	u32_t t1h;
	u32_t t1l;
	u32_t t2h;
	u32_t t2l;
	u8_t l;

	t2h = time_high;
	t2l = time_low;

	do {
		t1h = t2h;
		t1l = t2l;
		l = TCNT0;
		t2h = time_high;
		t2l = time_low;
	} while ( t1l != t2l );

	return ((u64_t)t1h << 32) + t1l + l;
}
#endif

#endif
