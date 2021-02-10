/* led85.c - led blinking application
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
#include <avr/pgmspace.h>

#define ledpin  PB1
#define btnpin	PB0

#if ledpin != 1
#error "ledpin != 1"
#endif
#if btnpin != 0
#error "btnpin != 0"
#endif
#if ASYNC_TX_PIN != 3
#error "ASYNC_TX_PIN != 2"
#endif

int main(void)
{
	u8_t count = 0;
	timing_init();
	pin_mode(ledpin, OUTPUT);
	pin_mode(btnpin, PULLUP);
	async_init();
	enable();
	puts_P(PSTR("Hello, world!\n"));

	for (;;)
	{
		delay_ms(20);

		if ( pin_get(btnpin) )
		{
			// Pin is high --> button is not pressed
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

void blubb(u8_t b)
{
}
