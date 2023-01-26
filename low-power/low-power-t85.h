/* low-power-t85.h - tinylib configuration
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
#ifndef LOW_POWER_T85_H
#define LOW_POWER_T85_H	1

#define ASYNC_TX_PORT	'B'
#define ASYNC_TX_PIN	PB4
#define ASYNC_BITRATE	9600
#define PASSIVE_TIME	1
#define INT_LOCK		0
#define HZ				1000000

#endif
