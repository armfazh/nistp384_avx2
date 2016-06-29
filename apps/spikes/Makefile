
include ../../common.mk

.PHONY: main ssl

all: main

main: $(BIN)/main_$(CC)

nettle: nettle.c ../bench/clocks.o
	$(CC) -o $(BIN)/nettle_$(CC)  $(CFLAGS) $^ -lhogweed -lnettle -lgmp

ssl: ssl.c ../bench/clocks.o
	$(CC) -o $(BIN)/ssl_$(CC)  $(CFLAGS) $^ -lssl -lcrypto 

$(BIN)/%_$(CC): %.c $(SRC)/random.o ../bench/clocks.o
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)

clean: 
	rm -rf $(BIN)/main_$(CC)

