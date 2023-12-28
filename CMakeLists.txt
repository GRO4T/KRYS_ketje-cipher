cmake_minimum_required(VERSION 3.10)

project(Ketje VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
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
add_subdirectory(lib/Ketje_XKCP)

# Build tests
enable_testing()
# Test Ketje XKCP implementation
add_executable(KetjeXKCPTest test/test_ketje_xkcp.cpp)
target_include_directories(KetjeXKCPTest PRIVATE lib/Ketje_XKCP)
target_link_libraries(KetjeXKCPTest PRIVATE GTest::GTest KetjeXKCPImpl)
add_test(UnitTests KetjeXKCPTest)

# Build source
add_executable(Ketje main.cpp src/monkeyduplex.cpp src/padding.cpp)
target_include_directories(Ketje PRIVATE include)
target_link_libraries(Ketje PRIVATE KetjeXKCPImpl)