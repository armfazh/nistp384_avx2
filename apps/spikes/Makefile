
include ../../common.mk

.PHONY: main

all: main

main: $(BIN)/main_$(CC)

$(BIN)/%_$(CC): %.c $(SRC)/random.c
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)

clean: 
	rm -rf $(BIN)/main_$(CC)

