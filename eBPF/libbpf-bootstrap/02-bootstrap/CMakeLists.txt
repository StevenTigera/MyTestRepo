cmake_minimum_required(VERSION 3.16)
project(02_bootstrap C)

set(CMAKE_C_STANDARD 11)
link_directories(libbpf/src)

add_executable(02_bootstrap bootstrap.c)
target_link_libraries(02_bootstrap bpf elf z)
