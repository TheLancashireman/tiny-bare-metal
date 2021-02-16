/* bufio.c - bputc()/bgetc()
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
#include "tinyio.h"


char rbuf[RBSIZE+1];
u8_t rb_in;
u8_t rb_out;

/* bputc() - put a character into the ringbuffer
 *
 * Automatically add a CR before LF.
*/
void bputc(char ch)
{
	u8_t is = disable();
	u8_t next = rb_in + 1;
	if ( next > RBSIZE )
		next = 0;
	if ( rb_out != next )		// Equal means buffer full
	{
		rbuf[rb_in] = ch;
		rb_in = next;
	}
	(void)restore(is);
}

/* bgetc() - return next character from ringbuffer
 *
 * Returns -1 if buffer is empty
*/
int bgetc(void)
{
	int r;

	u8_t is = disable();
	if ( rb_out == rb_in )
		r = -1;
	else
	{
		r = rbuf[rb_out];
		rb_out++;
		if ( rb_out > RBSIZE )
			rb_out = 0;
	}
	(void)restore(is);

	return r;
}
