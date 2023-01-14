/* ds18b20.h - DS18B20 1-wire temperature sensor
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
#ifndef DS18B20_H
#define DS18B20_H	1

#include "tiny1w.h"

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
#define DS18B20_FN_READ_SP	0xbe
#define DS18B20_FN_WRITE_SP	0x4e
#define DS18B20_FN_COPY_SP	0x48
#define DS18B20_FN_RECALL_E	0xb8
#define DS18B20_FN_READ_POW	0xb4

/* An impossible temperature value. Used for errors
*/
#define DS18B20_INVALID_TEMP	0x8000

/* Length of the scratchpad (including CRC)
*/
#define DS18B20_SP_LEN			9

/* Default value of MCU pin
*/
#ifndef DS18B20_PIN
#define DS18B20_PIN				PB3
#endif

#define DS18B20_MASK			(1 << DS18B20_PIN)

static inline void ds18b20_send_command(u8_t cmd)
{
	w1_writebyte(DS18B20_MASK, cmd);
}

extern u16_t ds18b20_read_temp(void);

#endif
