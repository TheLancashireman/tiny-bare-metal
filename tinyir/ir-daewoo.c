/* ir-daewoo.c - IR receiver (Daewoo VCR)
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

/*	Data stream for Daewoo VCR handset
 *   
 *  ________          ____   _   _   _   _   _   _   _   _   ____   _   _   _   _   _   _   _   _   _________
 *          |________|    |_|x|_|x|_|x|_|x|_|x|_|x|_|x|_|x|_|    |_|x|_|x|_|x|_|x|_|x|_|x|_|x|_|x|_|
 *  I        a        b                                      b                                      I
 *
 *  Idle = 1
 *  Start of frame (a) = low  approx 8 ms
 *  Start of byte  (b) = high approx 4 ms
 *  Bit marker (_)     = low  approx 1ms
 *  Bit value (x)      = high approx 1 ms (0) or 2 ms(1)
*/

#define IR_IDLE		0	// Idling - wait for start of frame
#define IR_SOF		1	// Start of frame
#define IR_SOB		2	// Start of byte
#define IR_TIM		3	// Timing pulse
#define IR_BIT		4	// Bit pulse

#define IR_MS(x)	((x)/T0_RESOLUTION)

#define MIN_SOF		IR_MS(7000)
#define MAX_SOF		IR_MS(9000)
#define MIN_SOB		IR_MS(3000)
#define MAX_SOB		IR_MS(5000)
#define MIN_TIM		IR_MS(500)
#define MAX_TIM		IR_MS(1500)
#define MIN_BIT		IR_MS(500)
#define MIN_ONE		IR_MS(1500)
#define MAX_BIT		IR_MS(2500)

void ir_decode_daewoo(u32_t time_now, u8_t pin_now)
{
	if ( pin_now == ir.pinstate )	
		return;					// No change; spurious interrupt (or different pin changed)

	u32_t pwidth = time_now - ir.time;

	ir.pinstate = pin_now;
	ir.time = time_now;

	if ( pin_now )
	{
		// Low --> high transition: end of SOF or end of timing bit
		if ( ir.state == IR_SOF )
		{
			// End of SOF
			if ( pwidth > MIN_SOF && pwidth < MAX_SOF )
			{
				// SOF within limits - now in SOB
				ir.state = IR_SOB;
				ir.shiftreg = 0;
				ir.bit = 0;
			}
			else
			{
				// SOF out of spec - go back to idle
				ir.state = IR_IDLE;
			}
		}
		else if ( ir.state == IR_TIM )
		{
			// End of timing pulse between bits
			if ( pwidth > MIN_TIM && pwidth < MAX_TIM )
			{
				if ( ir.bit == 8 )
				{
					// After the timing pulse after bit 8, another start-of-byte pulse is expected
					ir.state = IR_SOB;
				}
				else if ( ir.bit < 16 )
				{
					// After other timing pulses a data bit is expected
					ir.state = IR_BIT;
				}
				else if ( ir.bit == 16 )
				{
					// 16 bits received; move to holding store and set new data flag
					ir.data = ir.shiftreg;
					ir.newdata = 1;
					ir.state = IR_IDLE;
				}
				else
				{
					// Too many timing pulses. Should never get here.
					ir.state = IR_IDLE;
				}
			}
			else
			{
				// Timing pulse out of spec - go back to idle
				ir.state = IR_IDLE;
			}
		}
		else
		{
			// Wrong state; return to idle
			ir.state = IR_IDLE;
		}
	}
	else
	{
		// High --> low transition: end of IDLE, end of SOB or end of data bit
		if ( ir.state == IR_IDLE )
		{
			// Idle state has indeterminate length - cannot measure because timer might have overflowed.
			ir.state = IR_SOF;
		}
		else if ( ir.state == IR_SOB )
		{
			if ( pwidth > MIN_SOB && pwidth < MAX_SOB )
			{
				// After start-of-byte pulse, a timing pulse is expected
				ir.state = IR_TIM;
			}
			else
			{
				// Start-of-byte pulse out of spec - go back to idle
				ir.state = IR_IDLE;
			}
		}
		else if ( ir.state == IR_BIT )
		{
			if ( pwidth > MIN_TIM && pwidth < MAX_TIM )
			{
				// Data pulse: 1 or 0. Shift the bit in, increment the counter
				ir.shiftreg = ir.shiftreg << 1;
				if ( pwidth > MIN_ONE )
					ir.shiftreg |= 0x01;
				ir.bit++;
			}
			else
			{
				// Data pulse out of spec - go back to idle
				ir.state = IR_IDLE;
			}
		}
		else
		{
			// Wrong state; return to idle
			ir.state = IR_IDLE;
		}
	}
}
