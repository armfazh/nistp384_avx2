
include ../../common.mk

.PHONY: main ssl

LDFLAGS+=-lssl -lcrypto

all: main

main: $(BIN)/main_$(CC)
ssl: $(BIN)/ssl_$(CC)

$(BIN)/%_$(CC): %.c $(SRC)/random.c
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)

clean: 
	rm -rf $(BIN)/main_$(CC)

