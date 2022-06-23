cmake_minimum_required(VERSION 3.16)
project(03_fentry C)

set(CMAKE_C_STANDARD 11)
link_directories(libbpf/src)

add_executable(03_fentry fentry.c)
target_link_libraries(03_fentry bpf elf z)



