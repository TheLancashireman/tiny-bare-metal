/* read-eeprom.c - read an EEPROM cell
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

/* read_eeprom() - read byte at given address
*/
u8_t read_eeprom(u8_t addr)
{
	EEARL = addr;	
	EECR = 0x01;	/* Read strobe */
	EECR = 0x00;	/* Clear read strobe. Is this nexessary? */
	return EEDR;
}
