/* attiny.c - gpio and delay functions for attiny
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
#include "attiny.h"

void pin_mode_m(u8_t bitmask, u8_t mode)
{
	u8_t s = disable();
	DDRB = (DDRB & ~bitmask) | ( (mode == OUTPUT) ? bitmask : 0 );
	// ToDo: pullup for input
	(void)restore(s);
}

void pin_set_m(u8_t bitmask, u8_t bitstate)
{
	u8_t s = disable();
	PORTB = (PORTB & ~bitmask) | bitstate;
	(void)restore(s);
}

void delay_ms(unsigned ms)
{
	register unsigned t;
	while ( ms > 0 )
	{
		t = (((unsigned long)HZ)*3)/16000;
		while ( t > 0 )
		{
			__asm__ __volatile__ ("nop");
			t--;
		}
		ms--;
	}
}

u8_t disable(void)
{
	u8_t s = SREG;
	__asm__ __volatile__ ("cli");
	return s;
}

u8_t restore(u8_t old)
{
	u8_t s = SREG;
	if ( old & 0x80)
	{
		__asm__ __volatile__ ("sei");
	}
	else
	{
		__asm__ __volatile__ ("cli");
	}
	return s;
}
