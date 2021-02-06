#include "attiny.h"

#define ledpin  1

int main(void)
{
	pin_mode(ledpin, OUTPUT);

	for (;;)
	{
		pin_set(ledpin, HIGH);
		delay_ms(20);
		pin_set(ledpin, LOW);
		delay_ms(1980);
	}

	return 0;
}
