/* ir-daewoo.h - IR receiver - daewoo VCR handset
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
#ifndef IR_DAEWOO_H
#define IR_DAEWOO_H	1

extern void ir_decode_daewoo(u32_t time_now, u8_t pin_now);

static inline void ir_decode(u32_t t, u8_t p)
{
	ir_decode_daewoo(t, p);
}

#endif
