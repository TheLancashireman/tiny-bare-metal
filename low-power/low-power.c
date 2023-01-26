/* low-power - experiments in reducing power consumption
 *
 * (c) David Haworth
 *
 *  This file is part of tiny-bare-metal.
 *
 *  ds18b20-serial is free software: you can redistribute it and/or modify
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

/*
 *                             |--v--|
 *                    PB5/Rst -|1   8|- Vcc
 *                        PB3 -|2   7|- PB2
 *                        PB4 -|3   6|- PB1
 *                        Gnd -|4   5|- PB0/PCINT0
 *                             |-----|
*/

#include "tinylib.h"
#include "tinyio.h"

#define SLEEP(x)		wdsleep(x)

int main(void)
{
	disable();

	/* Disable the watchdog. wdsleep re-enables when necessary
	*/
	MCUSR = 0;		// Ensure WDRF is clear
	WDTCR = 0x10;	// Set WDCE, clear others (disables watchdog)

	/* Power consumption reduction measures
	*/
	DIDR0 = 0x3f;	// Disable all data-in buffers
	ACSR = (1<<ACD);

	/* Initialise
	*/
	timing_init();
	async_init();

	/* Startup message
	*/
	putc('\n');
	putc('H');
	putc('i');
	putc('\n');

	s8_t count = 64;

	for (;;)
	{
		wdsleep(30);

		putc('.');
		if ( (--count) <= 0 )
		{
			putc('\n');
			count = 64;
		}
	}

	return 0;
}
