/* reverse-bits.c - reverse the bits in a byte
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

const u8_t __attribute__((__progmem__)) rev4[16] =
{	0x0,	// 0x0
	0x8,	// 0x1
	0x4,	// 0x2
	0xc,	// 0x3
	0x2,	// 0x4
	0xa,	// 0x5
	0x6,	// 0x6
	0xe,	// 0x7
	0x1,	// 0x8
	0x9,	// 0x9
	0x5,	// 0xa
	0xd,	// 0xb
	0x3,	// 0xc
	0xb,	// 0xd
	0x7,	// 0xe
	0xf		// 0xf
};

u8_t reverse_bits(u8_t b)
{
	return (rev4[b & 0xf] << 4) | rev4[b >> 4];
}
