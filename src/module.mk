sp := $(sp).x
dirstack_$(sp)	:= $(d)
d := $(dir)

dir := $(d)/container
include $(dir)/module.mk

d := $(dirstack_$(sp))
sp := $(basename $(sp))