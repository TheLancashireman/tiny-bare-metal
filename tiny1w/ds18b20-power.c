/* ds18b20-power.c - DS18B20 1-wire temperature sensor power control
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

/* ds18b20_power_on() - turn on power to device
*/
void ds18b20_power_on(void)
{
#ifdef DS18B20_POWER_PIN
	port_pin_set(DS18B20_POWER_PORT, DS18B20_POWER_PIN, 1);
	port_pin_mode(DS18B20_POWER_PORT, DS18B20_POWER_PIN, OUTPUT);
	wdpsleep(WDSLEEP_16ms);
#endif
}

/* ds18b20_power_off() - turn off power to device
*/
void ds18b20_power_off(void)
{
#ifdef DS18B20_POWER_PIN
	port_pin_set(DS18B20_POWER_PORT, DS18B20_POWER_PIN, 0);
	port_pin_mode(DS18B20_POWER_PORT, DS18B20_POWER_PIN, INPUT);
#endif
}
