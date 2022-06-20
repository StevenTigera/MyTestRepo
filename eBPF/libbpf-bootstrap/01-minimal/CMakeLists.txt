cmake_minimum_required(VERSION 3.16)
project(01_minimal C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
link_directories(libbpf libbpf/src)

add_executable(01_minimal minimal.c)
target_link_libraries(01_minimal bpf elf z)
