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

extern void ir_decode_daewoo(u32_t time_now, u8_t pin_now);

static inline void ir_decode(u32_t t, u8_t p)
{
	ir_decode_daewoo(t, p);
}

/* 
 * Buttons on the remote control, left to right, top to bottom
 *
 * Note that all the codes start with 0xa8, so only the 2nd byte is relevant
*/
IRBTN_ONOFF		0xa8a8
IRBTN_PROG		0xa89c
IRBTN_1			0xa880
IRBTN_2			0xa840
IRBTN_3			0xa8c0
IRBTN_TVVCR		0xa868
IRBTN_4			0xa820
IRBTN_5			0xa8a0
IRBTN_6			0xa860
IRBTN_AV		0xa86c
IRBTN_7			0xa8e0
IRBTN_8			0xa810
IRBTN_9			0xa890
IRBTN_ABOX		0xa8b8
IRBTN_SKIP30	0xa878
IRBTN_0			0xa800
IRBTN_SKIP		0xa8c8	
IRBTN_EJECT		0xa884
IRBTN_PAUSE		0xa888
IRBTN_REW		0xa808
IRBTN_PLAY		0xa870
IRBTN_FFWD		0xa8f0
IRBTN_STOP		0xa8b0
IRBTN_REC		0xa848
IRBTN_SPLP		0xa8d8
IRBTN_PRPLUS	0xa8e8
IRBTN_MENU		0xa844
IRBTN_PALSEC	0xa8f8
IRBTN_LEFT		0xa88c
IRBTN_OK		0xa894
IRBTN_RIGHT		0xa8ac
IRBTN_IPLUS		0xa8fc
IRBTN_IMINUS	0xa8cc
IRBTN_PRMINUS	0xa818
IRBTN_ASEL		0xa858


#endif
