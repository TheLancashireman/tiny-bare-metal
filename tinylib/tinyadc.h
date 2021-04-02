/* tinyadc.h - header file for tinylib A/D conversion
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
#ifndef TINYADC_H
#define TINYADC_H	1

#include <avr/io.h>

// Bit fields in ADMUX
#define ADMUX_REFS		( (1 << REFS2) | (1 << REFS1) | (1 << REFS0) )
#define ADMUX_ADLAR 	( 1 << ADLAR )
#define ADMUX_MUX		( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) )

// Values for the REFS field in ADMUX
#define ADMUX_VCC		( (0 << REFS2) | (0 << REFS1) | (0 << REFS0) )
#define ADMUX_EXT		( (0 << REFS2) | (0 << REFS1) | (1 << REFS0) )
#define ADMUX_1_1		( (0 << REFS2) | (1 << REFS1) | (0 << REFS0) )
#define ADMUX_2_56		( (1 << REFS2) | (1 << REFS1) | (0 << REFS0) )
#define ADMUX_2_56_C	( (1 << REFS2) | (1 << REFS1) | (1 << REFS0) )

// Values for the MUX field in ADMUX
#define ADMUX_PB5		( (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0) )
#define ADMUX_PB2		( (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (1 << MUX0) )
#define ADMUX_PB4		( (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0) )
#define ADMUX_PB3		( (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (1 << MUX0) )
#define ADMUX_PB44_1	( (0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (0 << MUX0) )
#define ADMUX_PB44_20	( (0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (1 << MUX0) )
#define ADMUX_PB43_1	( (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0) )
#define ADMUX_PB43_20	( (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) )
#define ADMUX_PB55_1	( (1 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0) )
#define ADMUX_PB55_20	( (1 << MUX3) | (0 << MUX2) | (0 << MUX1) | (1 << MUX0) )
#define ADMUX_PB52_1	( (1 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0) )
#define ADMUX_PB52_20	( (1 << MUX3) | (0 << MUX2) | (1 << MUX1) | (1 << MUX0) )
#define ADMUX_VBG		( (1 << MUX3) | (1 << MUX2) | (0 << MUX1) | (0 << MUX0) )
#define ADMUX_GND		( (1 << MUX3) | (1 << MUX2) | (0 << MUX1) | (1 << MUX0) )
#define ADMUX_TEMP		( (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) )

// Pseudo-pins to select additional A/D sources
#define APIN_TEMP		100
#define APIN_VBG		101

// Bit fields in ADCSRA
#define	ADCSR_EN		( 1 << ADEN )
#define ADCSR_SC		( 1 << ADSC )
#define ADCSR_ATE		( 1 << ADATE )
#define ADCSR_IF		( 1 << ADIF )
#define ADCSR_IE		( 1 << ADIE )
#define ADCSR_PS		( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) )

// Values for the ADPS field
#define ADCSR_PS_2		( (0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0) )
#define ADCSR_PS_4		( (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0) )
#define ADCSR_PS_8		( (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) )
#define ADCSR_PS_16		( (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0) )
#define ADCSR_PS_32		( (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0) )
#define ADCSR_PS_64		( (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0) )
#define ADCSR_PS_128	( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) )

// Bit fields in ADCSRB
#define	ADCSR_BIN		( 1 << BIN )
#define	ADCSR_ACME		( 1 << ACME )
#define	ADCSR_IPR		( 1 << IPR )
#define ADCSR_ADTS		( (1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0) )

// Values for the ADTS field (only if ATE=1)
#define ADCSR_FR		( (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0) )
#define ADCSR_AC		( (0 << ADTS2) | (0 << ADTS1) | (1 << ADTS0) )
#define ADCSR_EXT0		( (0 << ADTS2) | (1 << ADTS1) | (0 << ADTS0) )
#define ADCSR_T0CMA		( (0 << ADTS2) | (1 << ADTS1) | (1 << ADTS0) )
#define ADCSR_T0OFLO	( (1 << ADTS2) | (0 << ADTS1) | (0 << ADTS0) )
#define ADCSR_T0CMB		( (1 << ADTS2) | (0 << ADTS1) | (1 << ADTS0) )
#define ADCSR_PCIR		( (1 << ADTS2) | (1 << ADTS1) | (0 << ADTS0) )

// Bit fields in DIDR0
#define DIDR_ADC0D		( 1 << ADC0D )
#define DIDR_ADC1D		( 1 << ADC1D )
#define DIDR_ADC2D		( 1 << ADC2D )
#define DIDR_ADC3D		( 1 << ADC3D )
#define DIDR_AIN0D		( 1 << AIN0D )
#define DIDR_AIN1D		( 1 << AIN1D )

/* pin_mode_analogue() - set analogue mode for pin
 *
 * am = 0 ==> digital buffer enabled
 * am = 1 ==> digital buffer disabled
*/
static inline void pin_mode_analogue(u8_t pin, u8_t am)
{
	u8_t bit;

	switch ( pin )
	{
	case PB2:	bit = DIDR_ADC1D;	break;
	case PB3:	bit = DIDR_ADC3D;	break;
	case PB4:	bit = DIDR_ADC2D;	break;
	case PB5:	bit = DIDR_ADC0D;	break;
	default:	bit = 0;			break;
	}

	if ( am )
		DIDR0 |= bit;
	else
		DIDR0 &= ~bit;
}

/* select_adc_source() - select a source for the adc
*/
static inline void select_adc_pin(u8_t pin)
{
	u8_t mux;

	switch ( pin )
	{
	case PB2:			mux = ADMUX_PB2;	break;
	case PB3:			mux = ADMUX_PB3;	break;
	case PB4:			mux = ADMUX_PB4;	break;
	case PB5:			mux = ADMUX_PB5;	break;
	case APIN_TEMP:		mux = ADMUX_TEMP;	break;
	case APIN_VBG:		mux = ADMUX_VBG;	break;
											// ToDo: more "special" values for the other adc sources
	default:	return;						// Not an analogue pin - ignore
	}

	ADMUX = (ADMUX & ~ADMUX_MUX) | mux;
}

/* start_conversion() - start a conversion
*/
static inline void start_conversion(void)
{
	ADCSRA |= ADCSR_SC;
}

/* is_converting() - return true if ADC conversion is in progress
*/
static inline u8_t is_converting(void)
{
	return (ADCSRA & ADCSR_SC) != 0;
}

/* adc_clear_if() - clear the ADC interrupt flag
*/
static inline void adc_clear_if(void)
{
	ADCSRA |= ADCSR_IF;
}

/* read_adc() - return the ADC conversion result
 *
 * If ADLAR = 1 the 10-bit result must be right-shifted 6 bits by the caller.
 *
 * According to the datasheet, ADCL must be read before ADCH
*/
static inline u16_t read_adc(void)
{
	u16_t aval =  ADCL;
	return aval + ((u16_t)ADCH) * 256;
}

/* init_adc() - initialise the A/D converter
 *
 *	- vref and prescaler as specifies in parameters
 *	- ADLAR = 0
 * 	- MUX = 0
 *	- enabled
 *	- ADATE = 0 (no auto-trigger)
 *	- interrupt disabled
 *	- BIN
 *	- IPR
 *	- auto-trigger source = free-running (should be irrelevant)
*/
static inline void init_adc(u8_t vref, u8_t ps)
{
	ADMUX = (vref & ADMUX_REFS);			// Select Vref (ADLAR and MUX to zero)
	ADCSRA = ps & ADCSR_PS;					// Set the prescaler (EN, ATE and IE to zero)
	ADCSRA |= ADCSR_EN;						// Enable the ADC
	ADCSRB = ADCSRB & ADCSR_ACME;			// Clear all bits except ACME (clears BIN, IPR and ADTS)
}

#endif
