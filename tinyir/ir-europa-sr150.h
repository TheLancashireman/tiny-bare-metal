/* ir-europa-sr150.h - IR receiver header file for a satellite receiver handset marked "EUROPA SR-150"
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
#ifndef IR_EUROPA_SR150_H
#define IR_EUROPA_SR150_H	1

/*	Data stream for Europa SR-150 handset
 *   
 *  ________          ____   _   _   _   _   _   _   _   _  .....  _   _   _   _   _   _   _   _   _________
 *          |________|    |_|x|_|x|_|x|_|x|_|x|_|x|_|x|_|x|_....._|x|_|x|_|x|_|x|_|x|_|x|_|x|_|x|_|
 *  I        a        b                                      b                                      I
 *
 *  Idle = 1
 *  Start of frame (a) = low  approx 9 ms
 *  Start of word  (b) = high approx 4 ms
 *  Bit marker (_)     = low  approx 0.66ms
 *  Bit value (x)      = high approx 0.5 ms (0) or 1.5 ms(1)   32 of these
 *
 *  ________          ____   ______
 *          |________|    |_|
 *  I        a       b                                      b                                      I
 *
 *  Idle = 1
 *  Start of frame  (a) = low  approx 9 ms
 *  Start of repeat (b) = high approx 2 ms
 *  Bit marker (_)      = low  approx 0.66ms
*/

/* 32-bit shift register and 8-bit key data needed
*/
typedef u32_t ir_sr_t;
typedef u8_t ir_key_t;

#if IR_USE_NEW_DECODER

#define IR_DECODER_TYPE     'A'
#define ir_decode(t, p)     ir_decoder_A(t, p)

#else

#define IR_DECODER_TYPE     'X'
extern void ir_decode_europa_sr150(u32_t time_now, u8_t pin_now);
#define ir_decode(t, p)     ir_decode_europa_sr150(t, p)

#endif

/* Decoder configuration (bit timing, etc.)
 *
 * There is no special repeat signal from this handset. The keycode just repeats.
 * There is a separator between bytes, after timing bit 9.
 * The upper 8 bits of the raw code are always 0xa800.
 * There is no checksum in the raw code.
*/

#define IR_NBITS		33				// Total number of timing bits

#define IR_MIN_SOF		IR_MS(8000)
#define IR_MAX_SOF		IR_MS(10000)
#define IR_MIN_SOW		IR_MS(3000)
#define IR_MAX_SOW		IR_MS(5000)
#define IR_MIN_TIM		IR_MS(560)
#define IR_MAX_TIM		IR_MS(760)
#define IR_MIN_BIT		IR_MS(100)
#define IR_MIN_ONE		IR_MS(1000)
#define IR_MAX_BIT		IR_MS(2500)

/* Repeat signal
*/
#define IR_MIN_SOR		IR_MS(1000)
#define IR_MAX_SOR		IR_MS(3000)

#define IR_FIXED_BITS	0xffff0000
#define IR_FIXED_VAL	0x12ed0000
#define IR_CHECKSUM(x)	( ( (u8_t)(~(u8_t)((x) >> 8)) ) == ( (u8_t)(x) ) )

#define IR_SR_TO_KEY(x)	((ir_key_t)(x))

/* 
 * Buttons on the remote control, left to right, top to bottom
 *
 * standby	0x12ed00ff
 * mute		0x12edc03f
 * mode		0x12eda05f
 * demp		0x12ed609f
 * digit_1	0x12ed10ef
 * digit_2	0x12ed906f
 * digit_3	0x12ed50af
 * ch_up	0x12edd02f
 * digit_4	0x12ed30cf
 * digit_5	0x12edb04f
 * digit_6	0x12ed708f
 * ch_dn	0x12edf00f
 * digit_7	0x12ed08f7
 * digit_8	0x12ed8877
 * digit_9	0x12ed48b7
 * digit_0	0x12eda857
 * vid_up	0x12ed18e7
 * ab		0x12ed9867
 * aud_up	0x12ed58a7
 * vid_dn	0x12ed38c7
 * vh		0x12edb847
 * aud_dn	0x12ed7887
 *
 * From this we can see that:
 *	- the first two bytes are always 0x12ed
 *	- the 3rd byte is the inverse of the 4th byte
 *	- the final digit is always f or 7
 *	- 
*/
#define IRBTN_STANDBY	0xff
#define IRBTN_MUTE		0x3f
#define IRBTN_MODE		0x5f
#define IRBTN_DEMP		0x9f
#define IRBTN_1			0xef
#define IRBTN_2			0x6f
#define IRBTN_3			0xaf
#define IRBTN_CH_UP		0x2f
#define IRBTN_4			0xcf
#define IRBTN_5			0x4f
#define IRBTN_6			0x8f
#define IRBTN_CH_DN		0x0f
#define IRBTN_7			0xf7
#define IRBTN_8			0x77
#define IRBTN_9			0xb7
#define IRBTN_0			0x57
#define IRBTN_VID_UP	0xe7
#define IRBTN_AB		0x67
#define IRBTN_AUD_UP	0xa7
#define IRBTN_VID_DN	0xc7
#define IRBTN_VH		0x47
#define IRBTN_AUD_DN	0x87

/* Error codes returned instead of keypress
*/
#define IRERR_CHK1		0x0e	// Upper 16 bits check error
#define IRERR_CHK2		0x1e	// Lower 16 bits checksum error

#define IR_ISERR(x)		(((x) & 0x0f) == 0x0e)


#endif
