
include ../../common.mk

.PHONY: tests
LDFLAGS+=-lssl -lcrypto

all: tests

tests: $(BIN)/tests_$(CC)

$(BIN)/tests_$(CC): $(SRC)/random.c tests.c test_Element_1w_h0h7.c test_Element_2w_h0h7.c test_pointmul.c
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)

clean: 
	rm -rf $(BIN)/tests_$(CC)
