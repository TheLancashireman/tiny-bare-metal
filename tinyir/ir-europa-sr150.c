/* ir-europa-sr150.c - Legacy IR receiver (Europa SR-150)
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

/* This decoder has been superseded by ir_decoder_A()
*/

//#define DBGC(x)	bputc(x)
#define DBGC(x)		do { } while (0)

/* State machine states
*/
#define IR_IDLE		0	// Idling - wait for start of frame
#define IR_SOF		1	// Start of frame
#define IR_SOW		2	// Start of word
#define IR_TIM		3	// Timing pulse
#define IR_BIT		4	// Bit pulse
#define IR_EOR		5	// Timing pulse

#if IR_DECODER_TYPE == 'X'
void ir_decode_europa_sr150(u32_t time_now, u8_t pin_now)
{
	if ( pin_now == ir.pinstate )	
		return;					// No change; spurious interrupt (or different pin changed)

	u32_t pwidth = time_now - ir.time;

	if ( pwidth >= 0xffffff00 )
	{
		// Timer overflow; but high order bits not updated yet.
		pwidth += 0x100;
		time_now += 0x100;
	}

	ir.pinstate = pin_now;
	ir.time = time_now;

	if ( pin_now )
	{
		// Low --> high transition: end of SOF or end of timing bit
		if ( ir.state == IR_SOF )
		{
			// End of SOF
			if ( pwidth > IR_MIN_SOF && pwidth < IR_MAX_SOF )
			{
				// SOF within limits - now in SOW
				ir.state = IR_SOW;
				ir.shiftreg = 0;
				ir.bit = 0;
				DBGC('1');
			}
			else
			{
				// SOF out of spec - go back to idle
				ir.state = IR_IDLE;
				DBGC('2');
			}
		}
		else if ( ir.state == IR_TIM )
		{
			// End of timing pulse between bits
			if ( pwidth > IR_MIN_TIM && pwidth < IR_MAX_TIM )
			{
				ir.bit++;

				if ( ir.bit < 33 )
				{
					// After timing pulses a data bit is expected
					ir.state = IR_BIT;
					DBGC('4');
				}
				else if ( ir.bit == 33 )
				{
					// Exactly 33 timing pulses received;
					// Check the data
					if ( (ir.shiftreg & IR_FIXED_BITS) == IR_FIXED_VAL )
					{
						if ( IR_CHECKSUM(ir.shiftreg) )
						{
							// OK; move to holding store and set new data flag
							ir.data = (ir_key_t)ir.shiftreg;
							DBGC('5');
						}
						else
						{
							// Checksum error
							ir.data = IRERR_CHK2;
							DBGC('F');
						}
					}
					else
					{
						// Fixed bits check error
						ir.data = IRERR_CHK1;
						DBGC('E');
					}
					ir.newdata = 1;
					ir.state = IR_IDLE;
				}
				else
				{
					// Too many timing pulses. Should never get here.
					ir.state = IR_IDLE;
					DBGC('6');
				}
			}
			else
			{
				// Timing pulse out of spec - go back to idle
				ir.state = IR_IDLE;
				DBGC('7');
			}
		}
		else if ( ir.state == IR_EOR )
		{
			// End of timing pulse after key-repeat
			if ( pwidth > IR_MIN_TIM && pwidth < IR_MAX_TIM )
			{
				// Timing pulse after repeat indicator: set indicator; key stays same.
				ir.newdata = 1;
				ir.state = IR_IDLE;
				DBGC('9');
			}
			else
			{
				// Timing pulse out of spec - go back to idle
				ir.state = IR_IDLE;
				DBGC('0');
			}
		}
		else
		{
			// Wrong state; return to idle
			ir.state = IR_IDLE;
			DBGC('8');
		}
	}
	else
	{
		// High --> low transition: end of IDLE, end of SOW or end of data bit
		if ( ir.state == IR_IDLE )
		{
			// Idle state has indeterminate length - cannot measure because timer might have overflowed.
			ir.state = IR_SOF;
			DBGC('a');
		}
		else if ( ir.state == IR_SOW )
		{
			if ( pwidth > IR_MIN_SOW && pwidth < IR_MAX_SOW )
			{
				// After start-of-word pulse, a timing pulse is expected
				ir.state = IR_TIM;
				DBGC('b');
			}
			else if ( pwidth > IR_MIN_SOR && pwidth < IR_MAX_SOR )
			{
				// After start-of-repeat pulse, a timing pulse is expected
				ir.state = IR_EOR;
				DBGC('r');
			}
			else
			{
				// Start-of-word pulse out of spec - go back to idle
				ir.state = IR_IDLE;
				DBGC('c');
			}
		}
		else if ( ir.state == IR_BIT )
		{
			if ( pwidth < IR_MIN_BIT )
			{
				// Data pulse too short - go back to idle
				ir.state = IR_IDLE;
				DBGC('d');
			}
			else if ( pwidth < IR_MAX_BIT )
			{
				// Data pulse: 1 or 0. Shift the bit in, increment the counter
				ir.shiftreg = ir.shiftreg << 1;
				if ( pwidth > IR_MIN_ONE )
					ir.shiftreg |= 0x01;
				ir.state = IR_TIM;
				DBGC('e');
			}
			else
			{
				// Data pulse too long - go back to idle
				ir.state = IR_IDLE;
				DBGC('f');
			}
		}
		else
		{
			// Wrong state; return to idle
			ir.state = IR_IDLE;
			DBGC('g');
		}
	}
}
#endif
