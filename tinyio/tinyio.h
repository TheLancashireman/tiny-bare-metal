/* tinyio.h - header file for tinyio
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
#ifndef TINYIO_H
#define TINYIO_H	1

#include "tinylib.h"
#include <avr/io.h>

// Async serial only if required
#ifndef ASYNC_BITRATE
#define ASYNC_BITRATE	0
#endif
#ifndef ASYNC_TX_PIN
#define ASYNC_TX_PIN	-1
#endif
#ifndef ASYNC_RX_PIN
#define ASYNC_RX_PIN	-1
#endif

#if ASYNC_BITRATE > 0

#if ASYNC_BITRATE == 9600
#define BIT_TIME	(104/T0_RESOLUTION)
#elif ASYNC_BITRATE == 4800
#define BIT_TIME	(208/T0_RESOLUTION)
#else
#error "Unsupported bit rate"
#endif

extern void putc(char c);
extern int puts(const char s[]);
extern int puts_P(const char s[]);
extern int printf(const char *fmt, ...);
extern void async_tx(u8_t ch);
extern u8_t bit_delay(u8_t t0);

#define TXCHAR(c)	async_tx((u8_t)c)

static inline void async_init(void)
{
#if ASYNC_TX_PIN >= PB0 && ASYNC_TX_PIN <= PB5
	pin_mode(ASYNC_TX_PIN, OUTPUT);
	pin_set(ASYNC_TX_PIN, 1);
#endif
#if ASYNC_RX_PIN >= PB0 && ASYNC_RX_PIN <= PB5
	pin_mode(ASYNC_RX_PIN, INPUT);
#endif
}

#endif

#endif
