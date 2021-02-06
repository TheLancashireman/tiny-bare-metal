# Makefile for led85 (tiny bare metal)

BUILD		?= build
GNU_D		?= /data1/projects/arduino/arduino-1.8.13/hardware/tools/avr
ISPPORT		?= /dev/ttyUSB0


GNU_BIN		?= $(GNU_D)/bin
OBJ_DIR		?= $(BUILD)/o

GCC			= $(GNU_BIN)/avr-gcc
GLD			= $(GNU_BIN)/avr-gcc
OBJCOPY		= $(GNU_BIN)/avr-objcopy

CC_OPT		+= -mmcu=attiny85
CC_OPT		+= -fdata-sections
CC_OPT		+= -ffunction-sections
CC_OPT		+= -Os
CC_OPT		+= -g
CC_OPT		+= -Wall

LD_OPT		+= -Os
LD_OPT		+= -mmcu=attiny85
LD_OPT		+= -Wl,--gc-sections
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
