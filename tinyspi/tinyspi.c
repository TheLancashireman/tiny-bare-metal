/* tinyspi.c - SPI protocol
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
#include "tinyspi.h"

/* spi_masterinit() - initialise USI as SPI master
*/
void spi_masterinit(void)
{
	pin_mode(PB2, OUTPUT);	/* SCK			*/
	pin_mode(PB1, OUTPUT);	/* DO (MOSI)	*/
	pin_mode(PB0, PULLUP);	/* DI (MISO)	*/

	USICR = TUSI_3WIRE | TUSI_SOFTCLK;
}

/* spi_writeread() - write data to SPI, return incoming data
*/
u8_t spi_writeread(u8_t data)
{
	USIDR = data;
	const u8_t clk0 = TUSI_3WIRE | TUSI_SOFTCLK | TUSI_TC;
	const u8_t clk1 = clk0 | TUSI_CLK;

	USICR = clk0;	/* Bit 7 */
	USICR = clk1;
	USICR = clk0;	/* Bit 6 */
	USICR = clk1;
	USICR = clk0;	/* Bit 5 */
	USICR = clk1;
	USICR = clk0;	/* Bit 4 */
	USICR = clk1;
	USICR = clk0;	/* Bit 3 */
	USICR = clk1;
	USICR = clk0;	/* Bit 2 */
	USICR = clk1;
	USICR = clk0;	/* Bit 1 */
	USICR = clk1;
	USICR = clk0;	/* Bit 0 */
	USICR = clk1;

	return USIDR;
}
