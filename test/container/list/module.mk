sp := $(sp).x
dirstack_$(sp)	:= $(d)
d := $(dir)

BINARIES += $(BIN_DIR)/sl_list_unit

$(BIN_DIR)/sl_list_unit: $(d)/sl_list_unit.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

d := $(dirstack_$(sp))
sp := $(basename $(sp))