# Bare metal programming on the attiny

This is a collection of bits for constructing attiny applications without the arduino environment.

The aim is for the memory footprint to be as small as absolutely possible, by letting the compiler
and linker do a lot of the work.

You need to install avr-gcc. On linux systems it might be just a matter of installing the gcc-avr package.
If gcc-avr isn't in the package repository, the easiest way might be to download and install arduino.

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
