include common.mk

all: $(TARGET)

$(TARGET): folder lib

lib: folder $(LIB)/lib$(TARGET)_$(CC).a

#$(LIB)/lib%_$(CC).a: $(SRC)/$(TARGET).o
$(LIB)/lib%_$(CC).a: $(SRC)/str_bytes.o  $(SRC)/random.o $(SRC)/element_1w_h0h7.o $(SRC)/element_2w_h0h7.o \
                     $(SRC)/ecc.o $(SRC)/pointmul.o
	$(AR) rcvs $@ $^

bench: $(BIN)/bench_$(CC)
papi: $(BIN)/papi_$(CC)
super: $(BIN)/super_$(CC)
test: $(BIN)/test_$(CC)

main: $(TARGET)
	make -C apps/spikes main

boringssl:
	make -C apps/spikes boringssl

openssl:
	make -C apps/spikes openssl

mbed:
	make -C apps/spikes mbed

nettle:
	make -C apps/spikes nettle

$(BIN)/%_$(CC): $(TARGET) apps/%
	make -C apps/$*

runall:
	for f in bin/bench_*; do \
	echo $$f;                \
	echo $$f>> log_bench;    \
	./$$f >> log_bench ;     \
	done

compileall:
	GCC=gcc CC=gcc make test bench
	#GCC=migcc4.8.5 CC=gcc make test bench
	GCC=migcc4.9.3 CC=gcc make test bench
	GCC=migcc5.1 CC=gcc make test bench
	GCC=migcc5.2 CC=gcc make test bench
	GCC=migcc5.3 CC=gcc make test bench
	CC=icc make test bench
	CC=clang make test bench

clean: 
	rm -rf $(LIB)/* $(BIN)/*

folder:
	@if [ ! -x $(LIB) ];	then mkdir $(LIB); 	fi
	@if [ ! -x $(BIN) ];	then mkdir $(BIN); 	fi

