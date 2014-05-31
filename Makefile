SHELL = /bin/sh
CC    = gcc
FLAGS        = 
CFLAGS       = -shared -fPIC 
DEBUGFLAGS   = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -fwhole-program
LDFLAGS      =
LIB_DIR = lib
BIN_DIR = bin
OBJECTS := 
BINARIES :=

TARGET := $(LIB_DIR)/libarc.so

vpath %.h include

all: $(TARGET) test

print-%:
	@echo '$*=$($*)'

$(TARGET):
	$(CC) $(FLAGS) $(CFLAGS) $(RELEASEFLAGS) $^ -o $(TARGET) $(LDFLAGS)

%.o: %.c
	 $(CC) -c -I include $(CFLAGS) $< -o $@

clean:
	rm $(TARGET) $(OBJECTS) $(BINARIES)

%: %.o
	$(CC) $@.o -o $@ 

dir	:= src
include $(dir)/module.mk

# dir	:= test
# include $(dir)/module.mk
