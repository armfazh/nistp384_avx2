cmake_minimum_required(VERSION 2.8.4)
project(nistp384_avx2)

include_directories(./include)
link_directories(./lib)
set(EXECUTABLE_OUTPUT_PATH ./bin)
set(LIBRARY_OUTPUT_PATH ./lib)
set(TARGET nistp384_avx2)
set(SRC ./src)
# PATH to BoringSSL, modify as appropriate.
set(BORINGSSL_PATH /home/armfazh/Downloads/boringssl)
enable_language(ASM-ATT)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -I./include -O3 -march=native -mtune=native")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wall -Wextra -O3 -march=native -mtune=native -flto -lm ")

add_library(${TARGET} STATIC
		${SRC}/str_bytes.c include/str_bytes.h
		${SRC}/element_1w_h0h7.c include/element_1w_h0h7.h
		${SRC}/element_2w_h0h7.c include/element_2w_h0h7.h
		${SRC}/ecc.c include/ecc.h
		${SRC}/pointmul.c include/pointmul.h
		)

add_executable(bench
		apps/bench/bench.c apps/bench/bench.h
		${SRC}/random.c include/random.h
		apps/bench/clocks.c apps/bench/clocks.h
		apps/bench/bench_Element_1w_h0h7.c
		apps/bench/bench_Element_2w_h0h7.c
		apps/bench/bench_ecc.c
		apps/bench/bench_pointmul.c
		)

add_executable(tests
		apps/tests/tests.c apps/tests/tests.h
		${SRC}/random.c include/random.h
		apps/tests/test_Element_1w_h0h7.c
		apps/tests/test_Element_2w_h0h7.c
		apps/tests/test_pointmul.c
		)



add_executable(main apps/spikes/main.c ${SRC}/random.c include/random.h)
add_executable(openssl apps/spikes/openssl.c ${SRC}/random.c apps/bench/clocks.c apps/bench/clocks.h)
add_executable(boringssl apps/spikes/boringssl.c ${SRC}/random.c apps/bench/clocks.c apps/bench/clocks.h)
add_executable(mbed apps/spikes/mbed.c ${SRC}/random.c apps/bench/clocks.c apps/bench/clocks.h)
add_executable(nettle_code apps/spikes/nettle.c ${SRC}/random.c apps/bench/clocks.c apps/bench/clocks.h)

target_link_libraries(
		bench
		crypto
		pthread
		${TARGET}
)
target_link_libraries(
		tests
		crypto
		pthread
		${TARGET}
)
target_link_libraries(
		main
		crypto
		${TARGET}
)

set_target_properties(boringssl PROPERTIES
		COMPILE_FLAGS "${COMPILE_FLAGS} -I${BORINGSSL_PATH}/include"
		LINK_FLAGS "-L${BORINGSSL_PATH}/build/crypto -L${BORINGSSL_PATH}/build/ssl"
		)
target_link_libraries(
		boringssl
		pthread
		crypto
		ssl
)
target_link_libraries(
		openssl
		crypto
		ssl
)
target_link_libraries(
		mbed
		mbedcrypto
		mbedtls
)
target_link_libraries(
		nettle_code
		hogweed
		nettle
		gmp
)
