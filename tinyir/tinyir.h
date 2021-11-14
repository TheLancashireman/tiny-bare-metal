/* tinyir.h - IR receiver
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
#ifndef TINYIR_H
#define TINYIR_H	1

#include "tinylib.h"

#ifdef TINYIR_REMOTE
#include TINYIR_REMOTE
#else
typedef u16_t ir_sr_t;
typedef u16_t ir_key_t;
static inline void ir_decode(u32_t t, u8_t p)
{
}
#endif

struct ir_s
{
	u32_t time;			// Time of last transition
	ir_sr_t shiftreg;	// Data shifted into this
	ir_key_t data;		// Complete keypress stored here
	u8_t bit;			// bit counter for shiftreg
	u8_t pinstate;		// Current/last state of pin
	u8_t state;			// Current decoder state
	u8_t newdata;		// Indicates that there's a new keypress in 'data'
};

extern struct ir_s ir;

extern void ir_init(void);
extern u8_t ir_receive(ir_key_t *data);

#endif
