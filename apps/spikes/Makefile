
include ../../common.mk

.INTERMEDIATE: main.o nettle.o openssl.o boringssl.o mbed.o ../bench/clocks.o
.PHONY: main nettle openssl boringssl mbed
BORINGSSL_PATH=/home/armfazh/Downloads/boringssl/build

all: main

main: $(BIN)/main_$(CC)

nettle: nettle.o ../bench/clocks.o
	$(CC) -o $(BIN)/nettle_$(CC)  $(CFLAGS) $^ -lhogweed -lnettle -lgmp

openssl: openssl.o ../bench/clocks.o
	$(CC) -o $(BIN)/openssl_$(CC)  $(CFLAGS) $^ -lssl -lcrypto

boringssl: boringssl.o ../bench/clocks.o
	$(CC) --verbose -o $(BIN)/boringssl_$(CC)  $(CFLAGS) $^ -lpthread -L$(BORINGSSL_PATH)/crypto -L$(BORINGSSL_PATH)//ssl -lcrypto -lssl

mbed: mbed.c ../bench/clocks.o
	$(CC) -o $(BIN)/mbed_$(CC)  $(CFLAGS) $^ -L/usr/local/lib -lmbedcrypto -lmbedtls

$(BIN)/%_$(CC): %.o $(SRC)/random.o ../bench/clocks.o
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)

clean: 
	rm -rf $(BIN)/main_$(CC)

