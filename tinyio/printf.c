/*	printf.c - tinylib formatted output
 *
 *	(c) David Haworth
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
#include <tinylib.h>
#include <tinyio.h>
#include <avr/pgmspace.h>

#include <string.h>
#include <ctype.h>
#include <stdarg.h>

/* We need to be able to print 32-bit numbers in decimal and hex.
 * 10 characters should be enough for that ;-)
*/
#define XPRINT_MAXSTR 20

static char *prt10(unsigned long val, char *str);
static char *prt16(unsigned long val, char *str, const char *hexdgt);

int printf(const char *fmt, ...)
{
	va_list ap;

	char ch, fill, string[XPRINT_MAXSTR+1], *str;
	int fmin, fmax, len, sign, ljust, longarg;
	int i, leading;
	int nprinted;
	long num;

	va_start(ap, fmt);
	nprinted = 0;

	while ( (ch = pgm_read_byte(fmt++)) != '\0' )
	{
		if ( ch == '%' )
		{
			ch = pgm_read_byte(fmt++);

			if ( ch == '%' )
			{
				putc('%');
				nprinted++;
			}
			else
			{
				sign = ljust = longarg = 0;
				fmin = 0;
				fmax = 255;
				fill = ' ';

				if ( ch == '-' )
				{
					ljust = 1;
					ch = pgm_read_byte(fmt++);
				}
				if ( ch == '0' )
				{
					fill = '0';
					ch = pgm_read_byte(fmt++);
				}
				if ( ch == '*' )
				{
					fmin = va_arg(ap,int);
					ch = pgm_read_byte(fmt++);
				}
				else
				while ( isdigit(ch) )
				{
					fmin = fmin * 10 + (ch - '0');
					ch = pgm_read_byte(fmt++);
				}
				if ( ch == '.' )
				{
					ch = pgm_read_byte(fmt++);
					if ( ch == '*' )
					{
						fmax = va_arg(ap,int);
						ch = pgm_read_byte(fmt++);
					}
					else
					{
						fmax = 0;
						while ( isdigit(ch) )
						{
							fmax = fmax * 10 + (ch - '0');
							ch = pgm_read_byte(fmt++);
						}
					}
				}
				if ( ch == 'l' )
				{
					longarg = 1;
					ch = pgm_read_byte(fmt++);
				}
				str = string;

				switch (ch)
				{
				case '\0':
					putc('%');
					return(nprinted+1);
					break;

				case 'c':
					if ( longarg )
						string[0] = (char) va_arg(ap, long);
					else
						string[0] = (char) va_arg(ap, int);
					string[1] = '\0';
					break;

				case 's':
					str = va_arg(ap, char*);
					break;

				case 'd':
				case 'u':
				case 'x':
				case 'X':
					if ( longarg )
						num = va_arg(ap, long);
					else
						num = va_arg(ap, int);
					if ( ch == 'd' && num < 0 )
					{
						sign = 1;
						num = -num;
					}
					if ( !longarg )
						num = (long)(int)num;
					if ( ch == 'd' || ch == 'u' )
						str = prt10(num, str);
					else
						str = prt16(num, str, ch=='x' ? PSTR("abcdef") : PSTR("ABCDEF"));
					break;

				default:
					string[0] = string[1] = string[2] = '?';
					string[3] = '\0';
					break;
				}
				leading = 0;
				len = strlen(str);
				if ( len > fmax )
					len = fmax;
				if ( len < fmin )
					leading = fmin - len - sign;
				nprinted += len + leading + sign;
				if ( sign && ( fill == '0' ) )
				{
					sign = 0;
					putc('-');
				}
				if ( !ljust )
					for ( i=leading; i>0; i-- )
						putc(fill);
				if ( sign )
					putc('-');
				for ( i=len; i>0; i-- )
					putc(*str++);
				if ( ljust )
					for ( i=leading; i>0; i-- )
						putc(fill);
			}
		}
		else
		{
			putc(ch);
			nprinted++;
		}
	}
	va_end(ap);
	return(nprinted);
}

static char *prt10(unsigned long val, char *str)
{
	unsigned long tmp;

	str += XPRINT_MAXSTR;
	*str = '\0';
	do
	{
		tmp = val / 10L;
		*(--str) = (val - tmp*10L) + '0';
		val = tmp;
	} while ( val != 0 );
	return(str);
}

static char *prt16(unsigned long val, char *str, const char *hexdgt)
{
	unsigned tmp;

	str += XPRINT_MAXSTR;
	*str = '\0';
	do
	{
		tmp = ((unsigned)val) & 0xF;
		if ( tmp < 10 )
			tmp += '0';
		else
			tmp = pgm_read_byte(&hexdgt[tmp-10]);
		*(--str) = tmp;
		val = val >> 4;
	} while ( val != 0 );
	return(str);
}
