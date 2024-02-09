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

/* On an AtTiny44:
 *	PB0 is XTAL1 and CLKI for external clock.
 *	PB1 is XTAL2
 *	PB2 is CKOUT, which might be useful for measurements.
 *	PB3 is RESET, which we can't use without a way of resetting the fuses.
 *
 * The remaining pins are PA0 to PA7
 * So let's use PA0 (pin 13) for the LED blink.
*/
#define ledpin  PA0
#define ledport 'A'

void delay(unsigned ms);

int main(void)
{
	# Set the prescaler to divide-by-1.
	# The first write enables the register; the second write (at most 4 clocks later) sets the value.
	CLKPR = 0x80;
	CLKPR = 0x00;

	port_pin_mode(ledport, ledpin, OUTPUT);

	for (;;)
	{
		port_pin_set(ledport, ledpin, HIGH);
		delay(20);
		port_pin_set(ledport, ledpin, LOW);
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
