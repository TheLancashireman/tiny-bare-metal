# Makefile for low-power

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
# along with tiny-bare-metal  If not, see <http://www.gnu.org/licenses/>.


AVR			?= t85

BUILD		?=	build
ISPPORT		?=	/dev/ttyUSB0
OBJ_DIR		?=	$(BUILD)/o
LIB_DIR		?=	$(BUILD)/a
TLIB_DIR	?=	../tinylib
TIO_DIR		?=	../tinyio

GCC			=	avr-gcc
GLD			=	avr-gcc
GAR			=	avr-ar
OBJCOPY		=	avr-objcopy

AVRDUDE_OPT	=	-P $(ISPPORT) -b 19200 -c avrisp -p $(AVR)

ifeq ($(AVR), t44)
GNU_MCU		:=	attiny44
HDR			:=	"\"low-power-t44.h\""
else ifeq ($(AVR), t85)
GNU_MCU		:=	attiny85
HDR			:=	"\"low-power-t85.h\""
else ifeq ($(AVR), t13)
GNU_MCU		:=	attiny13
HDR			:=	"\"low-power-t13.h\""
endif

CC_OPT		+=	-mmcu=$(GNU_MCU)
CC_OPT		+=	-D TINYLIB_CFG_HDR=$(HDR)
CC_OPT		+=	-fno-builtin
CC_OPT		+=	-Os
CC_OPT		+=	-g
CC_OPT		+=	-Wall
CC_OPT		+=	-I .
CC_OPT		+=	-I $(TLIB_DIR)
CC_OPT		+=	-I $(TIO_DIR)

LD_OPT		+=	-mmcu=$(GNU_MCU)
LD_OPT		+=	-Wl,--gc-sections
LD_OPT		+=	-Os
LD_OPT		+=	-L $(LIB_DIR)

LD_LIB		+=	-ltiny
LD_LIB		+=	-lm

OBJS		+=	$(OBJ_DIR)/low-power.o

VPATH		+=	$(TLIB_DIR)
VPATH		+=	$(TIO_DIR)

.PHONY:		default clean hex upload write_eeprom read_eeprom eew eer

default:	$(BUILD)/low-power.elf

clean:
	if [ -d $(BUILD) ] ; then rm -r $(BUILD); fi

hex:		$(BUILD)/low-power.ihex

$(BUILD)/o:
	mkdir -p $(BUILD)/o

$(BUILD)/low-power.elf:	$(OBJ_DIR) $(OBJS) $(LIB_DIR)/libtiny.a
	$(GLD) $(LD_OPT) -o $@ $(OBJS) $(LD_LIB)
	

$(OBJ_DIR)/%.o:	%.c
	$(GCC) $(CC_OPT) -o $@ -c $<

$(BUILD)/low-power.ihex:	$(BUILD)/low-power.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload:		$(BUILD)/low-power.ihex
	avrdude $(AVRDUDE_OPT) -U flash:w:build/low-power.ihex:i

write_eeprom:
	avrdude $(AVRDUDE_OPT) -U eeprom:w:$(EEP_ID),$(EEP_SLEEP):m

read_eeprom:
	avrdude $(AVRDUDE_OPT) -U eeprom:r:-:h

eew:	write_eeprom

eer:	read_eeprom

include $(TIO_DIR)/tinyio.make
include $(TLIB_DIR)/tinylib.make
