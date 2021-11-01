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
