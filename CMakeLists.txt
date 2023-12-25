cmake_minimum_required(VERSION 3.10)

project(Ketje VERSION 1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

add_subdirectory(lib/ketje)

add_executable(Ketje main.c)

target_include_directories(Ketje PRIVATE lib/ketje)

target_link_libraries(Ketje PRIVATE KetjeLib)