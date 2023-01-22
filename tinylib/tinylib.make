# Makefile fragment for tinylib

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

# Include this makefile fragment into your project makefile to build tinylib

# Prerequisites:
#	OBJ_DIR		- the directory to put the object files
#	LIB_DIR		- the directory to put the library
#	GAR			- the name of the GNU archiver program (including full path if necessary)
#				- a rule to compile a .c file to a .o file

#TINYL_OBJS	+=	$(OBJ_DIR)/pin-mode.o
#TINYL_OBJS	+=	$(OBJ_DIR)/pin-set.o
#TINYL_OBJS	+=	$(OBJ_DIR)/disable-restore.o
TINYL_OBJS	+=	$(OBJ_DIR)/timing.o
TINYL_OBJS	+=	$(OBJ_DIR)/sleep.o
TINYL_OBJS	+=	$(OBJ_DIR)/read-time.o
TINYL_OBJS	+=	$(OBJ_DIR)/read-time-32.o
TINYL_OBJS	+=	$(OBJ_DIR)/delay-ticks.o
TINYL_OBJS	+=	$(OBJ_DIR)/reverse-bits.o
TINYL_OBJS	+=	$(OBJ_DIR)/read-eeprom.o

$(LIB_DIR)/libtiny.a:	$(LIB_DIR) $(TINYL_OBJS)
	if [ -e $@ ] ; then rm $@; fi
	$(GAR) crus $@ $(TINYL_OBJS)

$(LIB_DIR):
	mkdir -p $@
