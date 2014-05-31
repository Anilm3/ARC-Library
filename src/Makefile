SHELL = /bin/sh
CC    = gcc

LIB_DIR     = ../lib
INCLUDE_DIR = ../include

CFLAGS  := -shared -fPIC -O2 -I $(INCLUDE_DIR)
LDFLAGS :=
OBJECTS := 

TARGET := $(LIB_DIR)/libarc.so
STATIC  := $(LIB_DIR)/libarc.a

vpath %.h $(INCLUDE_DIR)

all: $(STATIC) $(DYNAMIC)

dir	:= container
include $(dir)/module.mk

dir	:= test
include $(dir)/module.mk

print-%:
	@echo '$*=$($*)'

$(DYNAMIC): $(OBJECTS)
	$(CC) $(FLAGS) $(CFLAGS) $(RELEASEFLAGS) $^ -o $@ $(LDFLAGS)

$(STATIC): $(OBJECTS)
	ar rucs $@ $^

%.o: %.c
	 $(CC) -c -I include $(CFLAGS) $< -o $@

clean:
	rm $(DYNAMIC) $(STATIC) $(OBJECTS) $(BINARIES)

%: %.o
	$(CC) $@.o -o $@ 
