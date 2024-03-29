/* tinyusi.h - universal serial interface
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
#ifndef TINYUSI_H
#define TINYUSI_H	1

#include "tinylib.h"

/* USISR
*/
#define TUSI_SIF		( 1 << USISIF )
#define TUSI_OIF		( 1 << USIOIF )
#define TUSI_PF			( 1 << USIPF )
#define TUSI_DC			( 1 << USIDC )
#define TUSI_CNT		0x0f

/* USICR
*/
#define TUSI_SIE		( 1 << USISIE )
#define TUSI_OIE		( 1 << USIOIE )
#define TUSI_CLK		( 1 << USICLK )
#define TUSI_TC			( 1 << USITC )

#define TUSI_DISABLE	( (0 << USIWM1) | (0 << USIWM0) )
#define TUSI_3WIRE		( (0 << USIWM1) | (1 << USIWM0) )
#define TUSI_2WIRE		( (1 << USIWM1) | (0 << USIWM0) )
#define TUSI_2WIRE_OIF	( (1 << USIWM1) | (1 << USIWM0) )

#define TUSI_SOFTCLK	( (0 << USICS1) | (0 << USICS0) )
#define TUSI_TIM0		( (0 << USICS1) | (1 << USICS0) )
#define TUSI_EXTRISE	( (1 << USICS1) | (0 << USICS0) )
#define TUSI_EXTFALL	( (1 << USICS1) | (1 << USICS0) )

/* Pin assignments for various MCUs
 * The assignments can be overridden on the command line
*/
#ifndef USI_CLK_PORT

#if defined(PORTC) || defined(PORTD)
#error "Needs adapting for bigger devices"

#elif defined PORTA

/* Dual-port devices, e.g. ATtiny44
*/
#define USI_CLK_PORT	'A'
#define USI_CLK_PIN		PA4
#define USI_DO_PORT		'A'
#define USI_DO_PIN		PA5	
#define USI_DI_PORT		'A'
#define USI_DI_PIN		PA6

#else

/* Single-port devices, e.g. ATtiny85
*/
#define USI_CLK_PORT	'B'
#define USI_CLK_PIN		PB2
#define USI_DO_PORT		'B'
#define USI_DO_PIN		PB1	
#define USI_DI_PORT		'B'
#define USI_DI_PIN		PB0

#endif

#endif

#endif
