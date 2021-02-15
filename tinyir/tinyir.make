# Makefile fragment for tinyio

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
#		- see tinylib.make. This makefile adds files to tinylib.a

TINYL_OBJS	+=	$(OBJ_DIR)/tinyir.o
TINYL_OBJS	+=	$(OBJ_DIR)/ir-daewoo.o
