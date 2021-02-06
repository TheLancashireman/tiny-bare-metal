# tinylib

A library of functions for attiny microcontrollers.

The aim is for the memory footprint to be as small as absolutely possible, so we let the compiler
and linker do a lot of the work.

## Library functions

### Interrupt management
```
static inline void enable(void)
```
> Enables interrupts using the **sei** instruction.

```
u8_t disable(void)
```
> Disables interrupts using the **cli** instruction.<br/>
> Returns the value of the status register **SREG** prior to disabling.
```
u8_t restore(u8_t old)
```
> Restores the interrupt flag to a previous state using either **sei** or **cli**.<br/>
> Returns the value of the status register **SREG** prior to restoring.

### GPIO
```
void pin_mode(u8_t pin, u8_t mode)
```
> Sets the mode (OUTPUT/INPUT/PULLUP) of the pin.<br/>
> The pin is specified by number (0..5 or PB0..PB5)
```
void pin_set(u8_t pin, u8_t hilo)
```
> Sets the output state of the pin.<br/>
> The pin is specified by number (0..5 or PB0..PB5)
```
u8_t pin_get(u8_t pin)
```
> Gets the current state of the pin.<br/>
> The pin is specified by number (0..5 or PB0..PB5)
```
void pin_mode_m(u8_t bitmask, u8_t mode);
```
> Used by pin_mode().<br/>
> Sets the mode (OUTPUT/INPUT/PULLUP) of the pin.<br/>
> The pin is specified by mask (1 << pin_no)
```
void pin_set_m(u8_t bitmask, u8_t bitstate);
```
> Used by pin_set().<br/>
> Sets the output state of the pin.<br/>
> The pin is specified by mask (1 << pin_no). The state is either (1<<pin_no) or 0.

### Timing
The time-measurement API can measure time down to a resolution of T0_RESOLUTION microseconds -
the exact resolution depends on the clock frequency.

A 64-bit time is maintained, although for most purposes the 32-bit timing is sufficient.

```
void timing_init(void)
```
> Initialises Timer0 for use by the time-measurement features<br/>
> Erases all timer settings --> call before setting up PWM<br/>
```
u64_t read_time(void)
```
> Returns a 64-bit timestamp with resolution T0_RESOLUTION microseconds<br/>
> Times are monotonically increasing and will never overflow for all practical purposes<br/>
> CAVEAT: Might return incorrect time if called with interrupts disabled
```
u32_t read_time_32(void)
```
> Returns a 32-bit timestamp with resolution T0_RESOLUTION microseconds<br/>
> CAVEAT: Might return incorrect time if called with interrupts disabled
```
void delay_ticks(u32_t ticks)
```
> Delay for a specified number of ticks<br/>
> A tick is T0_RESOLUTION microseconds<br/>
> CAVEAT: Might delay forever if called with interrupts disabled
```
inline void delay_ms(u16_t ms)
```
> Delay for a specified number of milliseconds<br/>
> CAVEAT: Might delay forever if called with interrupts disabled
```
inline void delay_us(u32_t us)
```
> Delay for a specified number of microseconds<br/>
> CAVEAT: Might delay forever if called with interrupts disabled

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

