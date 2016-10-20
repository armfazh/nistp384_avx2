
include ../../common.mk

.PHONY: bench

all: bench 

bench: $(BIN)/bench_$(CC)

$(BIN)/bench_$(CC): clocks.c bench.c $(SRC)/random.c bench_Element_1w_h0h7.c \
                        bench_Element_2w_h0h7.c bench_ecc.c bench_pointmul.c
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)

clean:
	rm -rf $(BIN)/bench_$(CC)

