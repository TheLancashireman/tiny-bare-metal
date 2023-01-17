/* tinyir.c - IR receiver
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
#include "tinylib.h"
#include "tinyir.h"
#include "tinyio.h"
#include <avr/interrupt.h>

#ifdef IR_RX_PIN

/* ToDo: work out which pins can support IR. Perhaps it's just a matter
 * of generating the correct ISR for the PCINTx that's chosen
 * The current implementation only works for PCINT0 on an 8-pin device (ATtinyx5)
*/
#if IR_RX_PIN != 0
#error "Wrong pin"
#endif

#ifdef PORTA
#error "Needs work for use on a multi-port device."
#endif

struct ir_s ir;

/* PCINT0_vect() - handle a state change interrupt on the IR pin
 *
 * Note that this ISR will trigger for state changes for all pins that are enabled.
 * When another pin is monitored this way an interrupt demux is needed.
*/
ISR(PCINT0_vect)
{
	ir_decode(read_time_32(), pin_get(IR_RX_PIN));
}

/* ir_receive() - read out a new result from the IR decoder
*/
u8_t ir_receive(ir_key_t *data)
{
	if ( ir.newdata )
	{
		*data = ir.data;
		ir.newdata = 0;
		return 1;
	}
	return 0;
}

/* ir_init() - initialise the hardware for input and state-change interrupt
*/
void ir_init(void)
{
	u8_t is = disable();
	pin_mode(IR_RX_PIN, PULLUP);
	PCMSK |= (0x1 << IR_RX_PIN);
	GIMSK |= (0x1 << PCIE);
	(void)restore(is);
}

#endif
