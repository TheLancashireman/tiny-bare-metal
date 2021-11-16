/* ir-daewoo.h - IR receiver header file for unmarked DAEWOO VCR handset
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
#ifndef IR_DAEWOO_H
#define IR_DAEWOO_H	1

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

/* 16-bit shift register and 8-bit key data needed
*/
typedef u16_t ir_sr_t;
typedef u8_t ir_key_t;

#if IR_USE_NEW_DECODER

#define IR_DECODER_TYPE		'A'
#define ir_decode(t, p)		ir_decoder_A(t, p)

#else

#define IR_DECODER_TYPE		'Z'
extern void ir_decode_daewoo(u32_t time_now, u8_t pin_now);
#define ir_decode(t, p)		ir_decode_daewoo(t, p)

#endif

/* Decoder configuration (bit timing, etc.)
 *
 * There is no special repeat signal from this handset. The keycode just repeats.
 * There is a separator between bytes, after timing bit 9.
 * The upper 8 bits of the raw code are always 0xa800.
 * There is no checksum in the raw code.
*/

#define IR_NBITS		18				// Total number of timing bits

#define IR_MIN_SOF		IR_MS(7000)
#define IR_MAX_SOF		IR_MS(9000)
#define IR_MIN_SOW		IR_MS(3000)
#define IR_MAX_SOW		IR_MS(5000)
#define IR_MIN_TIM		IR_MS(100)
#define IR_MAX_TIM		IR_MS(1500)
#define IR_MIN_BIT		IR_MS(100)
#define IR_MIN_ONE		IR_MS(1200)
#define IR_MAX_BIT		IR_MS(2500)

#define IR_IS_SPACER(x)	((x) == 9)

#define IR_FIXED_BITS	0xff00			// Upper 8 bits ...
#define IR_FIXED_VAL	0xa800			// ... always a8
#define IR_CHECKSUM(x)	1				// Always OK

#define IR_SR_TO_KEY(x)	((ir_key_t)(x))

/* 
 * Buttons on the remote control, left to right, top to bottom
*/
#define IRBTN_ONOFF		0xa8
#define IRBTN_PROG		0x9c
#define IRBTN_1			0x80
#define IRBTN_2			0x40
#define IRBTN_3			0xc0
#define IRBTN_TVVCR		0x68
#define IRBTN_4			0x20
#define IRBTN_5			0xa0
#define IRBTN_6			0x60
#define IRBTN_AV		0x6c
#define IRBTN_7			0xe0
#define IRBTN_8			0x10
#define IRBTN_9			0x90
#define IRBTN_ABOX		0xb8
#define IRBTN_SKIP30	0x78
#define IRBTN_0			0x00
#define IRBTN_SKIP		0xc8	
#define IRBTN_EJECT		0x84
#define IRBTN_PAUSE		0x88
#define IRBTN_REW		0x08
#define IRBTN_PLAY		0x70
#define IRBTN_FFWD		0xf0
#define IRBTN_STOP		0xb0
#define IRBTN_REC		0x48
#define IRBTN_SPLP		0xd8
#define IRBTN_PRPLUS	0xe8
#define IRBTN_MENU		0x44
#define IRBTN_PALSEC	0xf8
#define IRBTN_LEFT		0x8c
#define IRBTN_OK		0x94
#define IRBTN_RIGHT		0xac
#define IRBTN_IMINUS	0xfc
#define IRBTN_IPLUS		0xcc
#define IRBTN_PRMINUS	0x18
#define IRBTN_ASEL		0x58

/* The last digit of the keycode is always a multiple of 4, so we can use 0x?e as error codes.
*/
#define IR_ISERR(x)		( ((x) & 0x0f) == 0x0e )

#define IRERR_CHK1		0x1e
#define IRERR_CHK2		0x2e

#endif
