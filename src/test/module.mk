sp := $(sp).x
dirstack_$(sp)  := $(d)
d := $(dir)

OBJECTS += $(d)/unit.o

#$(TARGET): $(d)/unit.o 

$(d)/unit.o : arc/test/unit.h

d := $(dirstack_$(sp))
sp := $(basename $(sp))


