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
*/
u16_t ds18b20_read_temp(void)
{
	ds18b20_start_conversion();

	if ( last_res != W1_OK )
		return ds18b20_invalid_temp();

	do {
		/* ToDo: low-power sleep; time limit */
	} while ( dsb1820_is_busy() );

	ds18b20_read_scratchpad();

	if ( last_res != W1_OK )
		return ds18b20_invalid_temp();

	if ( !dsb18b20_crc_ok() )
	{
		return ds18b20_invalid_temp();
	}

	return ds18b20_get_temp();
}
