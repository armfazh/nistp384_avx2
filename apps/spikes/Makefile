
include ../../common.mk

.PHONY: main ssl
BORINGSSL_PATH=/home/armfazh/Downloads/boringssl/build

all: main

main: $(BIN)/main_$(CC)

nettle: nettle.c ../bench/clocks.o
	$(CC) -o $(BIN)/nettle_$(CC)  $(CFLAGS) $^ -lhogweed -lnettle -lgmp

ssl: ssl.c ../bench/clocks.o
	$(CC) -o $(BIN)/ssl_$(CC)  $(CFLAGS) $^ -lssl -lcrypto

boringssl: boringssl.c ../bench/clocks.o
	$(CC) --verbose -o $(BIN)/boringssl_$(CC)  $(CFLAGS) $^ -lpthread -L$(BORINGSSL_PATH)/crypto -L$(BORINGSSL_PATH)//ssl -lcrypto -lssl

mbed: mbed.c ../bench/clocks.o
	$(CC) -o $(BIN)/mbed_$(CC)  $(CFLAGS) $^ -L/usr/local/lib -lmbedcrypto -lmbedtls

$(BIN)/%_$(CC): %.c $(SRC)/random.o ../bench/clocks.o
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)

clean: 
	rm -rf $(BIN)/main_$(CC)

