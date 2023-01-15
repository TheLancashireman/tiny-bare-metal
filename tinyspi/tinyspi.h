/* tinyspi.h - SPI protocol
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
#ifndef TINYSPI_H
#define TINYSPI_H	1

#include "tinylib.h"
#include "tinyusi.h"

/* Assume no debug trace if not specified
*/
#ifndef SPI_DBG
#define SPI_DBG	0
#endif

#if SPI_DBG
#include "tinyio.h"
#define SPI_PUTC(x)	putc(x)
#else
#define SPI_PUTC(x)	do { } while (0)
#endif

extern void spi_masterinit(void);
extern u8_t spi_writeread(u8_t data);

#endif
