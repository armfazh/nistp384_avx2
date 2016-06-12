
include ../../common.mk

.PHONY: bench bench_all

all: bench 

bench: $(BIN)/bench_$(CC)

bench_all: $(BIN)/bench_all_$(CC)_S_$(OMEGASTATIC)D_$(OMEGADYNAMIC)

$(BIN)/bench_$(CC):  clocks.c bench.c $(SRC)/random.c
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)

$(BIN)/bench_all_$(CC)_S_$(OMEGASTATIC)D_$(OMEGADYNAMIC): clocks.c bench_all.c $(SRC)/random.c bench_Element_1w_h0h7.c \
                        bench_Element_2w_h0h7.c bench_ecc.c bench_pointmul.c
	$(CC) -o $@  $(CFLAGS) $^ $(LDFLAGS)


clean: 
	rm -rf $(BIN)/bench_$(CC) $(BIN)/bench_all_$(CC) 

