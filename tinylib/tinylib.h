/* tinylib.h - header file for tinylib
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
#ifndef TINYLIB_H
#define TINYLIB_H	1

#include <avr/io.h>

// Assume full speed unless told otherwise.
#ifndef HZ
#define HZ	16000000
#endif

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned long u32_t;
typedef unsigned long long u64_t;

// Pin modes and states
#define LOW			0
#define HIGH		1
#define OUTPUT		2
#define PULLUP		3
#define PULLDOWN	4

extern void pin_mode_m(u8_t bitmask, u8_t mode);
extern void pin_set_m(u8_t bitmask, u8_t bitstate);
extern void delay_ms(unsigned ms);
extern u8_t disable(void);
extern u8_t restore(u8_t old);

static inline void pin_mode(u8_t pin, u8_t mode)
{
	pin_mode_m(0x1<<pin, mode);
}

static inline void pin_set(u8_t pin, u8_t hilo)
{
	pin_set_m(0x1<<pin, (hilo?(0x1<<pin):0x0));
}
#endif
