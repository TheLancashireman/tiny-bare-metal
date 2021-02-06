#include "attiny.h"

void pin_mode_m(u8_t bitmask, u8_t mode)
{
	u8_t s = disable();
	DDRB = (DDRB & ~bitmask) | ( (mode == OUTPUT) ? bitmask : 0 );
	// ToDo: pullup for input
	(void)restore(s);
}

void pin_set_m(u8_t bitmask, u8_t bitstate)
{
	u8_t s = disable();
	PORTB = (PORTB & ~bitmask) | bitstate;
	(void)restore(s);
}

void delay_ms(unsigned ms)
{
	register unsigned t;
	while ( ms > 0 )
	{
		t = (((unsigned long)HZ)*3)/16000;
		while ( t > 0 )
		{
			__asm__ __volatile__ ("nop");
			t--;
		}
		ms--;
	}
}

u8_t disable(void)
{
	u8_t s = SREG;
	__asm__ __volatile__ ("cli");
	return s;
}

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
