cmake_minimum_required(VERSION 3.14)
project(XO_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ===============================
# Try to find OpenSSL first
# ===============================
find_package(OpenSSL QUIET)

if(NOT OpenSSL_FOUND)
  message(STATUS "OpenSSL not found on system, fetching from source...")

  include(FetchContent)
  FetchContent_Declare(
    openssl
    URL https://www.openssl.org/source/openssl-3.0.13.tar.gz
  )

  FetchContent_MakeAvailable(openssl)

  # OpenSSL build produces static libs and headers in special folders
  # You may need to point to the paths explicitly if needed
  # Here we assume it will export OpenSSL::Crypto target
endif()

# ===============================
# Add source code as libraries
# ===============================
add_library(ai STATIC ai.cpp)
add_library(sys STATIC user_system.cpp)
add_library(game STATIC game_logic.cpp)

# ===============================
# Main executable
# ===============================
add_executable(xo_game game_wrapper.cpp)

if(OpenSSL_FOUND)
  target_link_libraries(xo_game ai sys game sqlite3 OpenSSL::Crypto)
else()
  target_link_libraries(xo_game ai sys game sqlite3 crypto)  # fallback to -lcrypto
endif()

# ===============================
# GoogleTest Setup
# ===============================
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_ai test_ai.cpp)
target_link_libraries(test_ai gtest_main ai)

include(GoogleTest)
gtest_discover_tests(test_ai)
