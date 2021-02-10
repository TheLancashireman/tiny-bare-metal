/* puts-p.s - puts_P()
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

/* puts_P() - transmit a character string from progmem over the selected serial port.
 *
 * Uses putc() for each character
*/
int puts_P(const char s[])
{
	int i = 0;
	char c;
	while ( (c = pgm_read_byte(&s[i])) != '\0' )
	{
		putc(c);
		i++;
	}
	return i;
}
