PROJECT = ratonjaquer
BUILD_DIR = ../bin
MY_INCLUDE_DIR = ../inc

CFILES = $(wildcard *.c)
AFILES = $(wildcard *.S)

CFLAGS += -g -O0

# TODO - you will need to edit these two lines!
DEVICE=stm32f103c8t6
OOCD_FILE = ../openocd-scripts/target/stm32f1x_chino.cfg
OOCD_INTERFACE = stlink

# You shouldn't have to edit anything below here.
INCLUDES += $(patsubst %,-I%, . $(MY_INCLUDE_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
