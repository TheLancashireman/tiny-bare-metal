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

/* If a configuration header is defined, include it.
 * This saves having a long command line and possibly awkward options
*/
#ifdef TINYLIB_CFG_HDR
#include TINYLIB_CFG_HDR
#endif

// Assume full speed unless told otherwise.
#ifndef HZ
#define HZ	16000000
#endif

// Assume active timing unless told otherwise
#ifndef PASSIVE_TIME
#define PASSIVE_TIME	0
#endif

// Assume interrupt locking needed unless told otherwise
#ifndef INT_LOCK
#define INT_LOCK		1
#endif

// Timer0 clock and resolution
#if HZ == 16000000
#define T0_CLKSEL			0x03	// Prescaler 64 --> 250 kHz
#define T0_PRESCALE			64
#define T0_RESOLUTION		4		// One tick = 4 us
#define INTERVALS_PER_SEC	61		// No of sleep intervals per second = HZ/(1024*256) rounded
#elif HZ == 8000000
#define T0_CLKSEL			0x03	// Prescaler 64 --> 125 kHz
#define T0_PRESCALE			64
#define T0_RESOLUTION		8		// One tick = 8 us
#define INTERVALS_PER_SEC	31		// No of sleep intervals per second = HZ/(1024*256) rounded
#elif HZ == 1200000
#define T0_CLKSEL			0x02	// Prescaler 8 --> 150 kHz
#define T0_PRESCALE			8
#define T0_RESOLUTION		6.666	// One tick = 6.666 us
#define INTERVALS_PER_SEC	5		// No of sleep intervals per second = HZ/(1024*256) rounded
#elif HZ == 1000000
#define T0_CLKSEL			0x02	// Prescaler 8 --> 125 kHz
#define T0_PRESCALE			8
#define T0_RESOLUTION		8		// One tick = 8 us
#define INTERVALS_PER_SEC	4		// No of sleep intervals per second = HZ/(1024*256) rounded
#else
#error "Unsupported HZ value"
#endif

#define ms_to_ticks(ms)		(((u32_t)(ms) * 1000)/T0_RESOLUTION)
#define us_to_ticks(us)		(((u32_t)(us) + T0_RESOLUTION  - 1)/T0_RESOLUTION)

// 64-bit time only if required. (Active timing only)
#ifndef TIME64
#define TIME64	0
#endif

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned long u32_t;
typedef unsigned long long u64_t;

typedef signed char s8_t;
typedef signed short s16_t;
typedef signed long s32_t;
typedef signed long long s64_t;

// Pin modes and states
#define LOW			0
#define HIGH		1
#define OUTPUT		2
#define INPUT		3
#define PULLUP		4

/* High-order time bits.
*/
#if !PASSIVE_TIME
#if TIME64
extern volatile u32_t time_high;
#endif
extern volatile u32_t time_low;
#endif

/* ===============================
 * Interrupt locking and unlocking
 * ===============================
*/
/* enable() - enable interrupts unconditionally
*/
static inline void enable(void)
{
	__asm__ __volatile__ ("sei");
}

/* disable() - disable interrupts using the cli instruction
 *
 * Returns the previous state of the status register (SREG)
*/
static inline u8_t disable(void)
{
	u8_t s = SREG;
	__asm__ __volatile__ ("cli");
	return s;
}

/* restore() - set the interrupt flag to a given state - usually the previous state returned by disable()
 *
 * Returns the state of the status register (SREG) prior to the restore
*/
static inline u8_t restore(u8_t old)
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

/* ==================================================
 * Interrupt locking and unlocking only when required
 * ==================================================
*/
#if INT_LOCK
static inline u8_t TL_disable(void)
{
	return disable();
}
static inline void TL_restore(u8_t s)
{
	(void)restore(s);
}
#else
static inline u8_t TL_disable(void)
{
	return 0;
}
static inline void TL_restore(u8_t s)
{
}
#endif

extern void timing_init(void);
extern void delay_ticks(u32_t ticks);
extern void sleep(u8_t n_intervals);
extern u8_t reverse_bits(u8_t b);
extern u8_t read_eeprom(u8_t addr);

#if !PASSIVE_TIME
extern u32_t read_time_32(void);
#if TIME64
extern u64_t read_time(void);
#endif
#endif

/* ATtinyx5 MCUs only have PORTB
 * These macros are provided for backwards compatibility
*/
#define pin_mode(pin, mode)		port_pin_mode('B', pin, mode)
#define pin_set(pin, state)		port_pin_set('B', pin, state)
#define pin_get(pin)			port_pin_get('B', pin)

/* port_pin_mode() - set the mode of a port/pin passed as letter/number
*/
static inline void port_pin_mode(char port, u8_t pin, u8_t mode)
{
	u8_t mask = (1 << pin);
	u8_t s = TL_disable();
#ifdef PORTA
	if ( port == 'A' )
	{
		if ( mode == OUTPUT )
			DDRA |= mask;
		else
			DDRA &= ~mask;
		if ( mode == PULLUP )
			PORTA |= mask;
		else
			PORTA &= ~mask;
	}
#endif
#ifdef PORTB
	if ( port == 'B' )
	{
		if ( mode == OUTPUT )
			DDRB |= mask;
		else
			DDRB &= ~mask;
		if ( mode == PULLUP )
			PORTB |= mask;
		else
			PORTB &= ~mask;
	}
#endif
#ifdef PORTC
	if ( port == 'C' )
	{
		if ( mode == OUTPUT )
			DDRC |= mask;
		else
			DDRC &= ~mask;
		if ( mode == PULLUP )
			PORTC |= mask;
		else
			PORTC &= ~mask;
	}
#endif
#ifdef PORTD
	if ( port == 'D' )
	{
		if ( mode == OUTPUT )
			DDRD |= mask;
		else
			DDRD &= ~mask;
		if ( mode == PULLUP )
			PORTD |= mask;
		else
			PORTD &= ~mask;
	}
#endif
	TL_restore(s);
}

/* port_pin_set() - set the state of a port/pin passed as a letter/number
*/
static inline void port_pin_set(char port, u8_t pin, u8_t state)
{
	u8_t mask = (1 << pin);
	u8_t s = TL_disable();
#ifdef PORTA
	if ( port == 'A' )
	{
		if ( state)
			PORTA = (PORTA  | mask);
		else
			PORTA = (PORTA & ~mask);
	}
#endif
#ifdef PORTB
	if ( port == 'B' )
	{
		if ( state)
			PORTB = (PORTB  | mask);
		else
			PORTB = (PORTB & ~mask);
	}
#endif
#ifdef PORTC
	if ( port == 'C' )
	{
		if ( state)
			PORTC = (PORTC  | mask);
		else
			PORTC = (PORTC & ~mask);
	}
#endif
#ifdef PORTD
	if ( port == 'D' )
	{
		if ( state)
			PORTD = (PORTD  | mask);
		else
			PORTD = (PORTD & ~mask);
	}
#endif
	TL_restore(s);
}

/* port_pin_get() - get the state of a port/pin passed as a letter/number
*/
static inline u8_t port_pin_get(char port, u8_t pin)
{
#ifdef PORTA
	if ( port == 'A' )
	{
		return (PINA & (0x1<<pin)) != 0x0;
	}
#endif
#ifdef PORTB
	if ( port == 'B' )
	{
		return (PINB & (0x1<<pin)) != 0x0;
	}
#endif
#ifdef PORTC
	if ( port == 'C' )
	{
		return (PINC & (0x1<<pin)) != 0x0;
	}
#endif
#ifdef PORTD
	if ( port == 'D' )
	{
		return (PIND & (0x1<<pin)) != 0x0;
	}
#endif
}

/* delay_ms() - delay for a number of milliseconds
*/
static inline void delay_ms(u16_t ms)
{
	delay_ticks(ms_to_ticks(ms));
}

/* delay_us() - delay for a number of microseconds
*/
static inline void delay_us(u32_t us)
{
	delay_ticks(us_to_ticks(us));
}

#endif
