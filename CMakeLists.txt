cmake_minimum_required(VERSION 3.14)
project(XO_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add your core source file
add_library(ai STATIC ai.cpp)
add_library(sys STATIC )
# GoogleTest Setup (Safe way to build + link)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Disable GoogleTest's own tests
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


enable_testing()

# Add your test executable
add_executable(test_ai test_ai.cpp)

# Link test with GoogleTest and your core library
target_link_libraries(test_ai gtest_main ai)

include(GoogleTest)
gtest_discover_tests(test_ai)

add_executable(test_ai_perf test_ai_perf.cpp)
target_link_libraries(test_ai_perf gtest_main ai)

gtest_discover_tests(test_ai_perf)

