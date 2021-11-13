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

extern void ir_decode_europa_sr150(u32_t time_now, u8_t pin_now);

static inline void ir_decode(u32_t t, u8_t p)
{
	ir_decode_europa_sr150(t, p);
}

/* 32-bit shift register needed
*/
typedef u32_t ir_sr_t;
typedef u32_t ir_key_t;

/* 
 * Buttons on the remote control, left to right, top to bottom
 *
 * standby	0x000000ff
 * mute		0x0000c03f
 * mode		0x0000a05f
 * demp		0x0000609f
 * digit_1	0x000010ef
 * digit_2	0x0000906f
 * digit_3	0x000050af
 * ch_up	0x0000d02f
 * digit_4	0x000030cf
 * digit_5	0x0000b04f
 * digit_6	0x0000708f
 * ch_dn	0x0000f00f
 * digit_7	0x000008f7
 * digit_8	0x00008877
 * digit_9	0x000048b7
 * digit_0	0x0000a857
 * vid_up	0x000018e7
 * ab		0x00009867
 * aud_up	0x000058a7
 * vid_dn	0x000038c7
 * vh		0x0000b847
 * aud_dn	0x00007887
 *
 * From this we can see that:
 *	- the first two bytes are always zero
 *	- the 3rd byte is the inverse of the 4th byte
 *	- 
*/
#define IRBTN_ONOFF		0xa8a8
#define IRBTN_PROG		0xa89c
#define IRBTN_1			0xa880
#define IRBTN_2			0xa840
#define IRBTN_3			0xa8c0
#define IRBTN_TVVCR		0xa868
#define IRBTN_4			0xa820
#define IRBTN_5			0xa8a0
#define IRBTN_6			0xa860
#define IRBTN_AV		0xa86c
#define IRBTN_7			0xa8e0
#define IRBTN_8			0xa810
#define IRBTN_9			0xa890
#define IRBTN_ABOX		0xa8b8
#define IRBTN_SKIP30	0xa878
#define IRBTN_0			0xa800
#define IRBTN_SKIP		0xa8c8	
#define IRBTN_EJECT		0xa884
#define IRBTN_PAUSE		0xa888
#define IRBTN_REW		0xa808
#define IRBTN_PLAY		0xa870
#define IRBTN_FFWD		0xa8f0
#define IRBTN_STOP		0xa8b0
#define IRBTN_REC		0xa848
#define IRBTN_SPLP		0xa8d8
#define IRBTN_PRPLUS	0xa8e8
#define IRBTN_MENU		0xa844
#define IRBTN_PALSEC	0xa8f8
#define IRBTN_LEFT		0xa88c
#define IRBTN_OK		0xa894
#define IRBTN_RIGHT		0xa8ac
#define IRBTN_IMINUS	0xa8fc
#define IRBTN_IPLUS		0xa8cc
#define IRBTN_PRMINUS	0xa818
#define IRBTN_ASEL		0xa858


#endif
