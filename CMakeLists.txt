cmake_minimum_required(VERSION 3.10)

project(Ketje VERSION 1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add GoogleTest
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# Add XKCP
add_subdirectory(lib/ketje)

# Build tests
enable_testing()
add_executable(KetjeTest test/test_keccak.cpp)
target_link_libraries(KetjeTest PRIVATE GTest::GTest)
add_test(UnitTests KetjeTest)

# Build source
add_executable(Ketje main.c)

target_include_directories(Ketje PRIVATE lib/ketje)

target_link_libraries(Ketje PRIVATE KetjeLib)