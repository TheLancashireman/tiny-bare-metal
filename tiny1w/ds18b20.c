/* ds18b20.c - DS18B20 1-wire temperature sensor
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
#include "ds18b20.h"

u8_t ds18b20_buffer[DS18B20_SP_LEN];
s8_t last_res;

/* The functions in this file all assume that the DS18B20 is the only 1-wire on the bus and
 * that it is operating with an external power supply.
 * Therefore:
 *		- no need to search the ROM or to read the ROM code
 *		- can use the Skip Rom code to address the device
 *		- can read the bus to detect end-of-conversion
*/

/* ds18b20_skip_rom() - reset the bus and send Skip Rom
*/
static inline void ds18b20_skip_rom(void)
{
	last_res = w1_busreset(DS18B20_MASK);

	if ( last_res == W1_OK )
	{
		ds18b20_send_command(DS18B20_ROM_SKIP);
	}
}

/* ds18b20_read_scratchpad() - read the entire contents of the scratchpad into the buffer
*/
void ds18b20_read_scratchpad(void)
{
	ds18b20_skip_rom();

	if ( last_res != W1_OK )
		return;

	ds18b20_send_command(DS18B20_FN_READ_SP);

	for ( s8_t i = 0; i < DS18B20_SP_LEN ; i++ )
	{
		ds18b20_buffer[i] = w1_readbyte(DS18B20_MASK);
	}
}

/* dsb18b20_crc_ok() - returns 1 if CRC good, 0 if bad
*/
s8_t dsb18b20_crc_ok(void)
{
	return 1;	/* ToDo: calculate and verify CRC */
}

/* ds18b20_start_conversion() - start a temperature conversion
*/
void ds18b20_start_conversion(void)
{
	ds18b20_skip_rom();

	if ( last_res != W1_OK )
		return;

	ds18b20_send_command(DS18B20_FN_CONVERT);
}
