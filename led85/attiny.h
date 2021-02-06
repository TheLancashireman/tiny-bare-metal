#ifndef ATTINY_H
#define ATTINY_H	1

#include <avr/io.h>

#ifndef HZ
#define HZ	16000000
#endif

typedef unsigned char u8_t;

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
