# Makefile for led-ir (tiny bare metal)

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
TIO_DIR		?=	../tinyio
TIR_DIR		?=	../tinyir

GCC			=	avr-gcc
GLD			=	avr-gcc
GAR			=	avr-ar
OBJCOPY		=	avr-objcopy

CC_OPT		+=	-mmcu=attiny85
CC_OPT		+=	-fno-builtin
CC_OPT		+=	-Os
CC_OPT		+=	-g
CC_OPT		+=	-Wall
CC_OPT		+=	-I $(TLIB_DIR)
CC_OPT		+=	-I $(TIO_DIR)
CC_OPT		+=	-I $(TIR_DIR)
CC_OPT		+=	-D ASYNC_BITRATE=9600
CC_OPT		+=	-D ASYNC_TX_PIN=PB4
CC_OPT		+=	-D IR_RX_PIN=PB0
CC_OPT		+=	-D RBSIZE=31

# Handset selection
CC_OPT		+=	-D TINYIR_REMOTE="\"ir-europa-sr150.h\""
#CC_OPT		+=	-D TINYIR_REMOTE="\"ir-daewoo.h\""

LD_OPT		+=	-mmcu=attiny85
LD_OPT		+=	-Wl,--gc-sections
LD_OPT		+=	-Os
LD_OPT		+=	-L $(LIB_DIR)

LD_LIB		+=	-ltiny
LD_LIB		+=	-lm

OBJS		+=	$(OBJ_DIR)/led-ir.o

VPATH		+=	$(TLIB_DIR)
VPATH		+=	$(TIO_DIR)
VPATH		+=	$(TIR_DIR)

.PHONY:		default clean hex upload

default:	$(BUILD)/led-ir.elf

clean:
	if [ -d $(BUILD) ] ; then rm -r $(BUILD); fi

hex:		$(BUILD)/led-ir.ihex

$(BUILD)/o:
	mkdir -p $(BUILD)/o

$(BUILD)/led-ir.elf:	$(OBJ_DIR) $(OBJS) $(LIB_DIR)/libtiny.a
	$(GLD) $(LD_OPT) -o $@ $(OBJS) $(LD_LIB)
	

$(OBJ_DIR)/%.o:	%.c
	$(GCC) $(CC_OPT) -o $@ -c $<

$(BUILD)/led-ir.ihex:	$(BUILD)/led-ir.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload:		$(BUILD)/led-ir.ihex
	avrdude -P $(ISPPORT) -b 19200 -c avrisp -p t85 -U flash:w:build/led-ir.ihex:i

include $(TIO_DIR)/tinyio.make
include $(TIR_DIR)/tinyir.make
include $(TLIB_DIR)/tinylib.make
