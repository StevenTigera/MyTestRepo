cmake_minimum_required(VERSION 3.16)
project(04_kprobe C)

set(CMAKE_C_STANDARD 11)
link_directories(libbpf/src)

add_executable(04_kprobe kprobe.c)
target_link_libraries(04_kprobe bpf elf z)
