sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

dir := $(d)/list
include $(dir)/module.mk

dir := $(d)/stack
include $(dir)/module.mk

d := $(dirstack_$(sp))
sp := $(basename $(sp))


