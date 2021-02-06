/* diasable-restore.c - disable and re-enable interrupt handling
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

/* disable() - disable interrupts using the cli instruction
 *
 * Returns the previous state of the status register (SREG)
*/
u8_t disable(void)
{
	u8_t s = SREG;
	__asm__ __volatile__ ("cli");
	return s;
}

/* restore() - set the interrupt flag to a given state - usually the previous state returned by disable()
 *
 * Returns the state of the status register (SREG) prior to the restore
*/
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
