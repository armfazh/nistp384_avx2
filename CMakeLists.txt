cmake_minimum_required(VERSION 2.8.4)
project(nistp384_avx2)

# set(CMAKE_BUILD_TYPE, None)
# set(CMAKE_INSTALL_PREFIX, "")
include_directories(./include)
link_directories(./lib)
set(EXECUTABLE_OUTPUT_PATH ./bin)
set(LIBRARY_OUTPUT_PATH ./lib)
set(TARGET nistp384_avx2)
set(SRC ./src)
enable_language(ASM-ATT)

set(CMAKE_C_FLAGS "-Wall -Wextra -I./include -L./lib -O3 -march=haswell -mtune=intel -mno-vzeroupper")

add_library(${TARGET} STATIC ${SRC}/${TARGET}.c src/element_1w_h0h7.c include/element_1w_h0h7.h)
add_library(${TARGET}_all STATIC ${SRC}/str_bytes.c src/element_1w_h0h7.c include/element_1w_h0h7.h)
#add_executable(bench apps/bench/bench.c apps/bench/clocks.c apps/bench/bench_ecdh_avx2.c ${SRC}/random.c )
#add_executable(test apps/test/test.c apps/test/test_ecdh_avx2.c ${SRC}/random.c)
#add_executable(bench_all apps/bench/bench_all.c apps/bench/clocks.c
#				${SRC}/random.c)
#add_executable(test_all apps/test/test_all.c
#				${SRC}/random.c)
add_executable(main apps/spikes/main.c ${SRC}/random.c)

# target_link_libraries(
#         bench
#         ${TARGET}
# )
# target_link_libraries(
#         test
#         ${TARGET}
# )
# target_link_libraries(
#         bench_all
#         ${TARGET}_all
# )
# target_link_libraries(
#         test_all
#         ${TARGET}_all
# )
target_link_libraries(
        main
        ${TARGET}_all
)
