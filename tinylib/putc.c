/* putc.c - putc()
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

#ifdef TXCHAR

/* putc() - transmit a character over the selected serial port.
 *
 * Automatically add a CR before LF.
*/
void putc(char ch)
{
	if ( ch == '\n' )
	{
		TXCHAR(0x0d);
		TXCHAR(0x0a);
	}
	else
		TXCHAR(ch);
}

#endif
