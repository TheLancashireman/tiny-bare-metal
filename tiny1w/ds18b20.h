/* ds18b20.h - DS18B20 1-wire temperature sensor
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

/* Length of the scratchpad (including CRC), and offsets
*/
#define DS18B20_SP_LEN			9
#define DS18B20_SP_TEMP_LSB		0
#define DS18B20_SP_TEMP_MSB		1
#define DS18B20_SP_TH			2		/* Upper alarm threshold */
#define DS18B20_SP_TL			3		/* Lower alarm threshold */
#define DS18B20_SP_CFG			4
#define DS18B20_SP_RES_FF		5
#define DS18B20_SP_RES			6
#define DS18B20_SP_RES_10		7
#define DS18B20_SP_CRC			8

/* Default value of MCU pin
*/
#ifndef DS18B20_PIN
#define DS18B20_PIN				PB3
#endif

#define DS18B20_MASK			(1 << DS18B20_PIN)

/* Error codes
*/
#define DS18B20_CVT_TIMEOUT		(T1W_DEV_ERR + 0)	// Timeout in conversion wait loop

/* Conversion time measurement - default to NO
*/
#ifndef DS18B20_CVT_TIME
#define DS18B20_CVT_TIME	0
#endif

extern u8_t ds18b20_buffer[DS18B20_SP_LEN];
extern s8_t last_res;
extern u8_t cvt_iter;

/* ds18b20_send_command() - send a command to the DS18B20
*/
static inline void ds18b20_send_command(u8_t cmd)
{
	t1w_writebyte(DS18B20_MASK, cmd);
}

/* dsb1820_is_busy() - check if device is busy after a long-duration command
*/
static inline s8_t dsb1820_is_busy(void)
{
	return (t1w_readbit(DS18B20_MASK) == 0);
}

/* ds18b20_get_temp() - get the temperature from the scratchpad buffer
*/
static inline u16_t ds18b20_get_temp(void)
{
	return ds18b20_buffer[DS18B20_SP_TEMP_LSB] + ds18b20_buffer[DS18B20_SP_TEMP_MSB] * 256;
}

/* ds18b20_invalid_temp() - return an invalid temperature incorporating the error code
*/
static inline u16_t ds18b20_invalid_temp(void)
{
	return DS18B20_INVALID_TEMP + last_res;
}

extern u16_t ds18b20_read_temp(void);
extern void ds18b20_read_scratchpad(void);
extern s8_t dsb18b20_crc_ok(void);
extern void ds18b20_start_conversion(void);

#endif
