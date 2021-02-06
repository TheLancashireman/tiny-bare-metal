# Makefile for led85 (tiny bare metal)

# Copyright David Haworth
# 
# This file is part of tiny-bare-metal.
# 
# tiny-bare-metal is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# tiny-bare-metal is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with tiny-bare-metal.  If not, see <http://www.gnu.org/licenses/>.


BUILD		?= build
ISPPORT		?= /dev/ttyUSB0


OBJ_DIR		?= $(BUILD)/o

GCC			= avr-gcc
GLD			= avr-gcc
OBJCOPY		= avr-objcopy

CC_OPT		+= -mmcu=attiny85
CC_OPT		+= -fdata-sections
CC_OPT		+= -ffunction-sections
CC_OPT		+= -Os
CC_OPT		+= -g
CC_OPT		+= -Wall

LD_OPT		+= -mmcu=attiny85
LD_OPT		+= -Wl,--gc-sections
LD_OPT		+= -Os
LD_OPT		+= -lm

OBJS		+= $(OBJ_DIR)/led85.o
OBJS		+= $(OBJ_DIR)/attiny.o

.PHONY:		default clean upload

default:	$(BUILD)/led85.elf

clean:
	if [ -d $(BUILD) ] ; then rm -r $(BUILD); fi

$(BUILD)/o:
	mkdir -p $(BUILD)/o

$(BUILD)/led85.elf:	$(OBJ_DIR) $(OBJS)
	$(GLD) $(LD_OPT) -o $@ $(OBJS) $(LD_LIB)
	

$(OBJ_DIR)/%.o:	%.c
	$(GCC) $(CC_OPT) -o $@ -c $<

$(BUILD)/led85.ihex:	$(BUILD)/led85.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload:		$(BUILD)/led85.ihex
	avrdude -P $(ISPPORT) -b 19200 -c avrisp -p t85 -U flash:w:build/led85.ihex:i
