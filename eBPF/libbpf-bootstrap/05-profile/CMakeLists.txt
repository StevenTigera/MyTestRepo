cmake_minimum_required(VERSION 3.16)
project(05_profile C)

set(CMAKE_C_STANDARD 11)
link_directories(libbpf/src)

add_executable(05_profile profile.c)
target_link_libraries(05_profile bpf elf z)