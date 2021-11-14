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

/* This project is an example of how to use the tinyir decoders.
 * It also acts as a test-bed for development of new decoders.
*/

#define ledpin  PB1

int main(void)
{
	u16_t count = 0;
	ir_sr_t ir_sr;
	ir_key_t ir_data;

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
			ir_sr = ir.shiftreg;

			if ( sizeof(ir_data) > 2 )
				printf(PSTR("\nkey = 0x%08lx  "), ir_data);
			else if ( sizeof(ir_data) > 1 )
				printf(PSTR("\nkey = 0x%04x  "), ir_data);
			else
				printf(PSTR("\nkey = 0x%02x  "), ir_data);

			if ( sizeof(ir_sr) > 2 )
				printf(PSTR("raw data = 0x%08lx\n"), ir_sr);
			else if ( sizeof(ir_sr) > 1 )
				printf(PSTR("raw data = 0x%04x\n"), ir_sr);
			else
				printf(PSTR("raw data = 0x%02x\n"), ir_sr);
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
