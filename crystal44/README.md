# crystal44

Demo program on attiny44 bare metal
* LED (PA0) blinks 20ms on, once every 2 seconds.

The aim is to get the AtTiny44 running with an external crystal and/or external clock.

The timing in this demo is done using timing loops. The demo sets the clock prescaler to
1 at startup, so is independent of the CKDIV8 fuse.

Commands to read the fuse bytes:
* avrdude -P $(ISPPORT) -b 19200 -c avrisp -p t44 -U lfuse:r:-:h
* avrdude -P $(ISPPORT) -b 19200 -c avrisp -p t44 -U hfuse:r:-:h
* avrdude -P $(ISPPORT) -b 19200 -c avrisp -p t44 -U efuse:r:-:h
* avrdude -P $(ISPPORT) -b 19200 -c avrisp -p t44 -U lock:r:-:h

First, get the demo working using the internal 8 MHz oscillator (defaul lfuse setting).

When it works, set the lfuse to 0x7f:
* Slow start
* Crystal oscillator >= 8 MHz

Put an 8 MHz crystal between pins 2 and 3, with an 18pF capacitor to ground on
each pin of the crystal. The same code should run with no noticable difference.

No arduino libraries were harmed during the construction of this application. :-)

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

