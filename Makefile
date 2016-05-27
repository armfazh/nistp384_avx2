include common.mk

all: $(TARGET)

$(TARGET): folder lib

lib: folder $(LIB)/lib$(TARGET)_$(CC).a
lib_all: folder $(LIB)/lib$(TARGET)_all_$(CC).a

#$(LIB)/lib%_$(CC).a: $(SRC)/$(TARGET).o
$(LIB)/lib%_$(CC).a: $(SRC)/str_bytes.o  $(SRC)/random.o
	$(AR) rcvs $@ $^

bench: $(BIN)/bench_$(CC)
papi: $(BIN)/papi_$(CC)
super: $(BIN)/super_$(CC)
test: $(BIN)/test_$(CC)

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

