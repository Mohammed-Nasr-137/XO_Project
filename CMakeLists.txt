cmake_minimum_required(VERSION 3.14)
project(XO_Project)

set(CMAKE_CXX_STANDARD 17)

# Add your core source file
add_library(ai STATIC ai.cpp)

# GoogleTest Setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add your test executable
add_executable(test_ai test_ai.cpp)

# Link test with GoogleTest and your core library
target_link_libraries(test_ai gtest_main ai)

include(GoogleTest)
gtest_discover_tests(test_ai)
