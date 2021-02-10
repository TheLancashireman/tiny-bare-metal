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

// Timer0 clock and resolution
#if HZ == 16000000
#define T0_CLKSEL			0x03	// Prescaler 64 --> 250 kHz
#define T0_RESOLUTION		4		// One tick = 4 us
#elif HZ == 8000000
#define T0_CLKSEL			0x03	// Prescaler 64 --> 125 kHz
#define T0_RESOLUTION		8		// One tick = 8 us
#elif HZ == 1000000
#define T0_CLKSEL			0x02	// Prescaler 8 --> 125 kHz
#define T0_RESOLUTION		8		// One tick = 8 us
#else
#error "Unsupported HZ value"
#endif

// 64-bit time only if required.
#ifndef TIME64
#define TIME64	0
#endif

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

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned long u32_t;
typedef unsigned long long u64_t;

// Pin modes and states
#define LOW			0
#define HIGH		1
#define OUTPUT		2
#define INPUT		3
#define PULLUP		4

/* High-order time bits.
*/
#if TIME64
extern volatile u32_t time_high;
#endif
extern volatile u32_t time_low;

extern void pin_mode_m(u8_t bitmask, u8_t mode);
extern void pin_set_m(u8_t bitmask, u8_t bitstate);
extern u8_t disable(void);
extern u8_t restore(u8_t old);
extern void timing_init(void);
extern u32_t read_time_32(void);
extern void delay_ticks(u32_t ticks);
extern u8_t reverse_bits(u8_t b);
extern void putc(char c);
extern int puts(const char s[]);
extern int puts_P(const char s[]);

#if TIME64
extern u64_t read_time(void);
#endif

#if ASYNC_BITRATE > 0
extern void async_tx(u8_t ch);
#define TXCHAR(c)	async_tx((u8_t)c)
//extern void blubb(u8_t ch);
//#define TXCHAR(c)	blubb((u8_t)c)
#endif

/* pin_mode() - set the mode of a pin passed as a pin number
*/
static inline void pin_mode(u8_t pin, u8_t mode)
{
	pin_mode_m(0x1<<pin, mode);
}

/* pin_set() - set the state of a pin passed as a pin number
*/
static inline void pin_set(u8_t pin, u8_t hilo)
{
	pin_set_m(0x1<<pin, (hilo?(0x1<<pin):0x0));
}

/* pin_get() - get the state of a pin passed as a pin number
*/
static inline u8_t pin_get(u8_t pin)
{
	return (PINB & (0x1<<pin)) != 0x0;
}

/* enable() - enable interrupts
*/
static inline void enable(void)
{
	__asm__ __volatile__ ("sei");
}

/* delay_ms() - delay for a number of milliseconds
*/
static inline void delay_ms(u16_t ms)
{
	delay_ticks(((u32_t)ms * 1000)/T0_RESOLUTION);
}

/* delay_us() - delay for a number of microseconds
*/
static inline void delay_us(u32_t us)
{
	delay_ticks((us + T0_RESOLUTION  - 1)/T0_RESOLUTION);
}

#if ASYNC_BITRATE > 0
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
