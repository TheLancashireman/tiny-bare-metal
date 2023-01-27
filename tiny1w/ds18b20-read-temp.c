/* ds18b20-read-temp.c - DS18B20 1-wire temperature sensor
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

/* Configuration of the wait loop.
 * The short-delay version is useful for measuring the conversion time.
*/
#if DS18B20_CVT_TIME
#define WDSLEEP			WDSLEEP_16ms
#define WDSLEEP_LIM		63
#else
/* Timing of conversion to be defined
*/
#define WDSLEEP			WDSLEEP_256ms
#define WDSLEEP_LIM		4
#endif

/* ds18b20_read_temp() - reads the temperature
 *
 * This is an all-in-one conversion and read function for projects that don't have anything else to
 * do during the conversion time.
 * The MCU goes to power-down during the wait loop.
*/
u16_t ds18b20_read_temp(void)
{
	ds18b20_start_conversion();

	if ( last_res != T1W_OK )
		return ds18b20_invalid_temp();

	s8_t lim = WDSLEEP_LIM;
	do {
		wdpsleep(WDSLEEP);
		lim--;
	} while ( dsb1820_is_busy() && ( lim > 0) );

	if ( lim <= 0 )
	{
		last_res = DS18B20_CVT_TIMEOUT;
		return ds18b20_invalid_temp();
	}

#if DS18B20_CVT_TIME
	cvt_iter = WDSLEEP_LIM - lim;
#endif

	ds18b20_read_scratchpad();

	if ( last_res != T1W_OK )
		return ds18b20_invalid_temp();

	if ( !dsb18b20_crc_ok() )
	{
		return ds18b20_invalid_temp();
	}

	return ds18b20_get_temp();
}
