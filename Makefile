SHELL = /bin/sh
CC    = gcc
FLAGS        = 
CFLAGS       = -fPIC 
DEBUGFLAGS   = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -fwhole-program
LDFLAGS      = -shared
LIB_DIR = lib

OBJECTS := 

TARGET := $(LIB_DIR)/arc.so

vpath %.h include

print-%:
	@echo '$*=$($*)'

$(TARGET):
	$(CC) $(FLAGS) $(CFLAGS) $(RELEASEFLAGS) $^ -o $(TARGET) $(LDFLAGS)

%.o: %.c
	 $(CXX) -c -I include $(CFLAGS) $< -o $@

clean:
	rm $(TARGET) $(OBJECTS)


dir	:= src
include $(dir)/module.mk
