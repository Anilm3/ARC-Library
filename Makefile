SHELL = /bin/sh
CC    = gcc
FLAGS        = 
CFLAGS       = -fPIC 
DEBUGFLAGS   = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -fwhole-program
LDFLAGS      = -shared

TARGET  = lib/arc.so

# save_dir =	sp := $(sp).x \
# 			dirstack_$(sp)  := $(d) \
# 			d := $(dir)

# restore_dir =	d := $(dirstack_$(sp)) \
# 				sp := $(basename $(sp))

vpath %.h include


$(TARGET):
	$(CC) $(FLAGS) $(CFLAGS) $(RELEASEFLAGS) $^ -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.c
	 $(CXX) -c -I include $(CFLAGS) $< -o $@

dir	:= src
include $(dir)/module.mk
