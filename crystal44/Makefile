# Makefile for crystal44 (tiny bare metal)

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


BUILD		?=	build
ISPPORT		?=	/dev/ttyUSB0
OBJ_DIR		?=	$(BUILD)/o
LIB_DIR		?=	$(BUILD)/a
TLIB_DIR	?=	../tinylib

GCC			=	avr-gcc
GLD			=	avr-gcc
GAR			=	avr-ar
OBJCOPY		=	avr-objcopy

CC_OPT		+=	-mmcu=attiny44
CC_OPT		+=	-fno-builtin
CC_OPT		+=	-Os
CC_OPT		+=	-g
CC_OPT		+=	-Wall
CC_OPT		+=	-I $(TLIB_DIR)
CC_OPT		+=	-D HZ=8000000

LD_OPT		+=	-mmcu=attiny44
LD_OPT		+=	-Wl,--gc-sections
LD_OPT		+=	-Os
LD_OPT		+=	-L $(LIB_DIR)

LD_LIB		+=	-ltiny
LD_LIB		+=	-lm

OBJS		+=	$(OBJ_DIR)/crystal44.o

VPATH		+=	$(TLIB_DIR)

.PHONY:		default clean hex upload

default:	$(BUILD)/crystal44.elf

clean:
	if [ -d $(BUILD) ] ; then rm -r $(BUILD); fi

hex:		$(BUILD)/crystal44.ihex

$(BUILD)/o:
	mkdir -p $(BUILD)/o

$(BUILD)/crystal44.elf:	$(OBJ_DIR) $(OBJS) $(LIB_DIR)/libtiny.a
	$(GLD) $(LD_OPT) -o $@ $(OBJS) $(LD_LIB)
	

$(OBJ_DIR)/%.o:	%.c
	$(GCC) $(CC_OPT) -o $@ -c $<

$(BUILD)/crystal44.ihex:	$(BUILD)/crystal44.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload:		$(BUILD)/crystal44.ihex
	avrdude -P $(ISPPORT) -b 19200 -c avrisp -p t44 -U flash:w:build/crystal44.ihex:i

include $(TLIB_DIR)/tinylib.make
