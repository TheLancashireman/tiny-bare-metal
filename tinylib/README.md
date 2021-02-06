# tinylib

A library of functions for attiny microcontrollers.

The aim is for the memory footprint to be as small as absolutely possible, so we let the compiler
and linker do a lot of the work.

## Library functions

### Interrupt management

```
static inline void enable(void)
```
* Enables interrupts using the **sei** instruction.

```
u8_t disable(void)
```
* Disables interrupts using the **cli*** instruction.
* Returns the value of the status register **SREG** prior to disabling.
```
u8_t restore(u8_t old)
```
* Restores the interrupt flag to a previous state using either **sei** or **cli***.
* Returns the value of the status register **SREG** prior to restoring.

### GPIO

### Timing

extern void pin_mode_m(u8_t bitmask, u8_t mode);
extern void pin_set_m(u8_t bitmask, u8_t bitstate);
extern void delay_ms(unsigned ms);
static inline void pin_mode(u8_t pin, u8_t mode)
static inline void pin_set(u8_t pin, u8_t hilo)
static inline u8_t pin_get(u8_t pin)

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

