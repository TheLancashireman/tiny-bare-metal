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

/* ds18b20_read_temp() - reads the temperature
 *
 * This is an all-in-one conversion and read function for projects that don't have anything else to
 * do during the conversion time.
 * The MCU goes to power-down during the wait loop.
 *
 * The waiting time is configurable. It consists of an initial call to wdpsleep(), followed by a limited
 * number of subsequent calls. The duration of the first and subsequent calls are separately configurable.
 * This allows tuning to achieve lowest power consumption.
*/
u16_t ds18b20_read_temp(void)
{
	ds18b20_pon();

	ds18b20_start_conversion();

	if ( last_res == T1W_OK )
	{
		wdpsleep(DS18B20_CVT_DLY_FIRST);

		u8_t i = 0;
		
		while ( dsb1820_is_busy() && ( i < DS18B20_CVT_DLY_LIM) )
		{
			wdpsleep(DS18B20_CVT_DLY_LOOP);
			i++;
		}

		ds18b20_store_cvt_time(i);
		if ( i >= DS18B20_CVT_DLY_LIM )
		{
			last_res = DS18B20_CVT_TIMEOUT;
		}
		else
		{
			ds18b20_read_scratchpad();
		}
	}

	ds18b20_poff();

	if ( last_res != T1W_OK )
		return ds18b20_invalid_temp();

	if ( !dsb18b20_crc_ok() )
	{
		return ds18b20_invalid_temp();
	}

	return ds18b20_get_temp();
}
