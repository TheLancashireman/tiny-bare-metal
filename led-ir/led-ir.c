/* led-ir.c - led blinking application, testbed for IR receiver
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
#include "tinyir.h"
#include <avr/pgmspace.h>

#define ledpin  PB1

int main(void)
{
	u16_t count = 0;
	u16_t ir_data;

	timing_init();
	pin_mode(ledpin, OUTPUT);
	async_init();
	ir_init();
	enable();
	printf(PSTR("Hello, world!\n"));

	for (;;)
	{
		delay_ms(1);

		if ( count == 0 )
		{
			pin_set(ledpin, HIGH);
			bputc('-');
		}
		else
		if ( count == 20 )
			pin_set(ledpin, LOW);

		count++;
		if ( count >= 2000 )
			count = 0;

		if ( ir_receive(&ir_data) )
		{
			printf(PSTR("\nir_data = 0x%04x\n"), ir_data);
		}

		int c = bgetc();
		while ( c >= 0 )
		{
			putc(c);
			c = bgetc();
		}
	}

	return 0;
}
