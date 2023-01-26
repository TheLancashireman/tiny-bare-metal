/* async-tx.c - asynchronous serial transmit
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
#include "tinyio.h"

#if ASYNC_BITRATE != 0

#if ASYNC_TX_PIN >= 0 && ASYNC_TX_PIN <= 7

void async_tx(u8_t ch)
{
	u8_t t, i = 8;
	t = TCNT0;


	port_pin_set(ASYNC_TX_PORT, ASYNC_TX_PIN, ASYNC_TX_BIT(0));					// Start bit
	t = bit_delay(t);

	while ( i > 0 )
	{
		port_pin_set(ASYNC_TX_PORT, ASYNC_TX_PIN,  ASYNC_TX_BIT(ch & 0x01));	// Data bit
		ch = ch >> 1;
		i--;
		t = bit_delay(t);
	}

	port_pin_set(ASYNC_TX_PORT, ASYNC_TX_PIN, ASYNC_TX_BIT(1));					// Stop bit
	(void)bit_delay(t);
}

#endif

#endif
