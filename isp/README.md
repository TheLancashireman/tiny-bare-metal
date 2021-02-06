# ArduinoISP

This is an AVR programmer constructed as an arduino sketch.

The original came from the arduino 1.8.13 release, but wouldn't compile.

The sketch works on a nano. It should work on other 5v arduinos too.

The completed ISP works with avrdude. The programmer type is avrisp.

## To compile

Use the IDE is probably the easiest way. For the command line you'll have to obtain the
Arduino CLI makefile from somewhere, and adapt the Makefile.

If you're using the command line, "make upload" should flash it into a nano.

## To build a programmer

Connect three LEDs with 100R series resistors between pins D7, D8 and D9 and GND. I used
green for the heartbeat (pin D9), yellow for activity (pin D7) and red for error (pin D8).

After programming the nano, connect a 10uF capacitor between RST and GND. That prevents
the nano from resetting when a program on the host opens the ttyUSB port. If you're
building a permanent programmer it's a good idea to use a jumper in series with the
capacitor so that you can take it out of circuit if/when you want to update the
ISP firmware.

You can test the programmer now by plugging it in. The three LEDs will flash in sequence, then
the heartbeat LED will start beating.

Try running avrdude. It should connect with the programmer, but fail (obviously) because there's no
attiny connected.

Now you can connect the attiny to the programmer:

     attiny      --->   nano
     Pin 8 (5v)         5v
     Pin 4 (Gnd)        GND
     Pin 1 (Reset)      D10
     Pin 5              D11
     Pin 6              D12
     Pin 7              D13

If you're building a permanent programmer, use an IC socket or (even better) a ZIF socket.

avrdude should now be able to read the signature and the fuse bytes.
     
## avrdude command

avrdude -P /dev/ttyUSBx -b 19200 -c avrisp -p t85 -U [....]

t85 is for an attiny85. Type avrdude -p ? for a full list.

## License

BSD. See the source file and http://www.opensource.org/licenses/bsd-license.php for details.
