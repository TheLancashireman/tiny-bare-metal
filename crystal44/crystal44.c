/* crystal44.c - application to demonstrate clocking an AtTiny44 with a crystal
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

#define ledpin  PB1

void delay(unsigned ms);

int main(void)
{
	pin_mode(ledpin, OUTPUT);

	for (;;)
	{
		pin_set(ledpin, HIGH);
		delay(20);
		pin_set(ledpin, LOW);
		delay(1980);
	}

	return 0;
}

void delay(unsigned ms)
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
