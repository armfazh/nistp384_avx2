
include ../../common.mk

.PHONY: test test_all

all: test_all

test: $(BIN)/test_$(CC) 

test_all: $(BIN)/test_all_$(CC)

$(BIN)/test_$(CC): test.c $(SRC)/random.c
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)

$(BIN)/test_all_$(CC): $(SRC)/random.c test_all.c test_Element_1w_h0h7.c
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)

clean: 
	rm -rf $(BIN)/test_$(CC) $(BIN)/test_all_$(CC)
