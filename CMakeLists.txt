cmake_minimum_required(VERSION 3.14)
project(XO_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# AI Logic as a static library
add_library(ai STATIC ai.cpp)
add_library(sys STATIC user_system.cpp)
# Main game executable
add_executable(xo_game main.cpp)
target_link_libraries(xo_game ai sys)

# GoogleTest Setup for testing (optional but useful)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test binary
add_executable(test_ai test_ai.cpp)
target_link_libraries(test_ai gtest_main ai)

include(GoogleTest)
gtest_discover_tests(test_ai)
