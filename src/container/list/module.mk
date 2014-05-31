sp := $(sp).x
dirstack_$(sp)  := $(d)
d := $(dir)

OBJECTS += $(d)/sl_list.o $(d)/dl_list.o

$(TARGET): $(d)/sl_list.o $(d)/dl_list.o

$(d)/sl_list.o : arc/container/list/sl_list.h
$(d)/dl_list.o : arc/container/list/dl_list.h

d := $(dirstack_$(sp))
sp := $(basename $(sp))


