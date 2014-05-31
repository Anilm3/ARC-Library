SHELL = /bin/sh
CC    = gcc

LIB_DIR     = ../lib
INCLUDE_DIR = ../include
BIN_DIR     = ../bin

OBJECTS := 
BINARIES :=

CFLAGS  := -O2 -I $(INCLUDE_DIR)
LDFLAGS := $(LIB_DIR)/libarc.a

vpath %.h $(INCLUDE_DIR)

dir	:= container
include $(dir)/module.mk

all: $(BINARIES)

print-%:
	@echo '$*=$($*)'

clean:
	rm $(OBJECTS) $(BINARIES)

