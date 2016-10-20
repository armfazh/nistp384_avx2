
include ../../common.mk

.PHONY: test
LDFLAGS+=-lssl -lcrypto

all: test

test: $(BIN)/test_$(CC) 

$(BIN)/test_$(CC): $(SRC)/random.c test_all.c test_Element_1w_h0h7.c test_Element_2w_h0h7.c test_pointmul.c
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)

clean: 
	rm -rf $(BIN)/test_$(CC)
