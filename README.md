# Bare metal programming on the attiny85

This is a collection of bits for constructing attiny85 applications without the arduino environment.
They will probably work on the other attinyx5 chips too, and (with modification) on other AVR
microcontrollers.

The aim is for the memory footprint to be as small as possible, by letting the compiler
and linker do a lot of the work.

You need to install avr-gcc. On linux systems it might be just a matter of installing the gcc-avr package.
If gcc-avr isn't in the package repository, the easiest way might be to download and install arduino.

You'll also need avrdude and an in-system programmer. For a quick & dirty programmer, look in isp/. Or
build my "Joat" project.

# Useful avrdude commands

Program an Intel-hex file called FILENAME.ihex into the attiny:
```
avrdude -P <SERIALPORT> -b 19200 -c avrisp -p t85 -U flash:w:FILENAME.ihex:i
```

Set the LFUSE to VAL:
```
avrdude -P <SERIALPORT> -b 19200  -c avrisp -p t85 -U lfuse:w:VAL:m
```

Some useful LFUSE values:
* 0x62 - CKSEL = 2 (internal 8 MHz oscillator) CKDIV8 = 0 (divide by 8) --> 1 MHz
* 0xe2 - CKSEL = 2 (internal 8 MHz oscillator) CKDIV8 = 1 (divide by 1) --> 8 MHz
* 0xe1 - CKSEL = 1 (PLL/4 = 16 MHz) CKDIV8 = 1 (divide by 1) --> 16 MHz

## License, disclaimer etc.

The ArduinoISP is licensed under the BSD license: see http://www.opensource.org/licenses/bsd-license.php

For the rest of the code:

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
