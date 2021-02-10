# led-button-serial

LED blink program on attiny85 bare metal - 20ms on, once every 2 seconds.
If the button is pressed the blink mode changes to 250 ms on / 250 ms off.

At startup, transmit a friendly message at 9600 BPS bit-banged.
Every blink, transmt a character.

The timing in this sketch uses the tinylib timing on Timer0.

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

