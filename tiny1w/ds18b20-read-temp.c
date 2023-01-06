/* ds18b20-read-temp.c - DS18B20 1-wire temperature sensor
 *
 * (c) David Haworth
 *
 *  This file is part of one-wire.
 *
 *  one-wire is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  one-wire is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with one-wire.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ds18b20.h"

#if 0

/* DS18B20 ROM command codes
*/
#define DS18B20_ROM_SEARCH	0xf0
#define DS18B20_ROM_READ	0x33
#define DS18B20_ROM_MATCH	0x55
#define DS18B20_ROM_SKIP	0xcc
#define DS18B20_ROM_ALM_SCH	0xec

/* DS18B20 function codes
*/
#define DS18B20_FN_CONVERT	0x44
#define DS18B20_FN_READ_SP	0x4e
#define DS18B20_FN_WRITE_SP	0xbe
#define DS18B20_FN_COPY_SP	0x48
#define DS18B20_FN_RECALL_E	0xb8
#define DS18B20_FN_READ_POW	0xb4


#define DS18B20_INVALID_TEMP	0x8000
#define DS18B20_SP_LEN			9
#ifndef DS18B20_PIN
#define DS18B20_PIN				3
#endif

#endif

static u8_t ds18b20_buffer[DS18B20_SP_LEN];
static s8_t last_res;

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
	last_res = w1_reset(DS18B20_PIN);
	if ( last_res == W1_OK )
	{
		ds18b20_send_command(DS18B20_ROM_SKIP);
	}
}

/* dsb1820_is_busy() - check if device is busy after a long-duration command
*/
static inline s8_t dsb1820_is_busy(void)
{
	return (w1_read(DS18B20_PIN) == 0);
}

/* dsb1820_read_scratchpad() - read the entire contents of the scratchpad into the buffer
*/
void dsb1820_read_scratchpad(void)
{
	ds18b20_skip_rom();

	if ( last_res != W1_OK )
		return;

	ds18b20_send_command(DS18B20_FN_READ_SP);

	for ( s8_t i = 0; i < DS18B20_SP_LEN ; i++ )
	{
		ds18b20_buffer[i] = w1_readbyte(DS18B20_PIN);
	}
}

/* dsb18b20_crc_ok() - returns 1 if CRC good, 0 if bad
*/
s8_t dsb18b20_crc_ok(void)
{
	return 1;	/* FIXME: to do */
}

/* ds18b20_read_temp() - reads the temperature
*/
u16_t ds18b20_read_temp(void)
{
	ds18b20_skip_rom();

	if ( last_res != W1_OK )
		return DS18B20_INVALID_TEMP;

	ds18b20_send_command(DS18B20_FN_CONVERT);

	while ( dsb1820_is_busy() )
	{
	}

	dsb1820_read_scratchpad();

	if ( last_res != W1_OK )
		return DS18B20_INVALID_TEMP;

	if ( dsb18b20_crc_ok() )
	{
		return ds18b20_buffer[0] + ds18b20_buffer[1] * 256;
	}
	else
	{
		return DS18B20_INVALID_TEMP;
	}
}
