# tinyio

stdio functions for attiny microcontrollers.

The aim is for the memory footprint to be as small as absolutely possible, so we let the compiler
and linker do a lot of the work.

## Library functions
```
void async_tx(u8_t ch)
```
> Transmit a single byte by bit-banging on an output pin selected by ASYNC_TX_PIN.
> Define ASYNC_TX_PIN on the compiler command line - e.g. -DASYNC_TX_PIN=PB2
> async_tx() is used by putc()
```
u8_t bit_delay(u8_t t0)
```
> Delay one bit time starting from t0.<br/>
> Returns end time of the delay.<br/>
> Define ASYNC_BITRATE on the compiler command line to select the bit rate. Supported: 9600 and 4800.
```
inline void async_init(void)
```
> Initialise the bit-banged serial I/O pins.
```
void putc(char c)
```
> Transmit a single character using the uart. If the character is '\n', precede it with '\r'
```
int puts(const char s[])
```
> Transmit a normal character string via the uart.<br/>
> Returns the number of characters, excluding '\r' padding for '\n'.
```
int puts_P(const char s[])
```
> Transmit a progmem character string via the uart.<br/>
> Returns the number of characters, excluding '\r' padding for '\n'.
```
int printf(const char *fmt, ...)
```
> A stripped-down version of the stdio printf() using the uart.<br/>
> The format string *must* be a progmem string.<br/>
> Supported formats: c, s, d, u, x, X. Supported field modifiers: -, 0, *, ., l.<br/>
> Strings for the 's' format must be normal strings, not progmem.<br/>
> CAVEAT: printf uses about 1100 bytes of flash.


## License, disclaimer etc.

Copyright David Haworth

This file is part of tiny-bare-metal.

tiny-bare-metal is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

tiny-bare-metal is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with tiny-bare-metal.  If not, see <http://www.gnu.org/licenses/>.

