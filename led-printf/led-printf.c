/* led-printf.c - led blinking/button application - printf() example
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
#include "tinyio.h"
#include <avr/pgmspace.h>

#define ledpin  PB1
#define btnpin	PB0

u8_t btnstate;

int main(void)
{
	u8_t count = 0;
	timing_init();
	pin_mode(ledpin, OUTPUT);
	pin_mode(btnpin, PULLUP);
	async_init();
	enable();
	printf(PSTR("Hello, world!\n"));
	printf(PSTR("Decimal: %d\n"), 42);
	printf(PSTR("Hexadecimal: 0x%x 0x%X\n"), 42, 0xab);

	for (;;)
	{
		delay_ms(20);

		if ( pin_get(btnpin) )
		{
			// Pin is high --> button is not pressed
			if ( btnstate )
			{
				printf(PSTR("Button %s%c"), "off", '\n');
				btnstate = 0;
			}
			if ( count == 0 )
			{
				pin_set(ledpin, HIGH);
				putc('-');
			}
			else
				pin_set(ledpin, LOW);
		}
		else
		{
			// Pin is low --> button is pressed
			if ( !btnstate )
			{
				printf(PSTR("Button %s%c"), "on", '\n');
				btnstate = 1;
			}
			if ( count < 50 )
				pin_set(ledpin, HIGH);
			else
				pin_set(ledpin, LOW);
		}

		count++;

		if ( count >= 100 )
			count = 0;
	}

	return 0;
}
