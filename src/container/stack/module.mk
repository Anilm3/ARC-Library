sp := $(sp).x
dirstack_$(sp)  := $(d)
d := $(dir)

OBJECTS += $(d)/stack_lf.o $(d)/stack_ts.o

$(TARGET): $(d)/stack_lf.o $(d)/stack_ts.o

$(d)/stack_lf.o : arc/container/stack/stack_lf.h
$(d)/stack_ts.o : arc/container/stack/stack_ts.h

d := $(dirstack_$(sp))
sp := $(basename $(sp))


