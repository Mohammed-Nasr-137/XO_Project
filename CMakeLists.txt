cmake_minimum_required(VERSION 3.14)
project(XO_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable Qt's automatic code generation
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

# Your core libraries
add_library(ai STATIC ai.cpp)
add_library(sys STATIC user_system.cpp)
add_library(game STATIC game_logic.cpp)
add_library(wrapper STATIC game_wrapper.cpp)

# Build the Qt GUI executable (signup screen for now)
# List all your .cpp/.h/.ui files here so CMake processes the UIs
set(GUI_SOURCES
    main.cpp 
    signup.cpp
    signup.h
    signup.ui
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    mainscreen.cpp
    mainscreen.h
    mainscreen.ui
    # turnpage.cpp
    # turnpage.h
    # turnpage.ui
    # aipage.cpp
    # aipage.h
    # aipage.ui
    # ... add any other .cpp/.h/.ui you need
)

add_executable(xo_game ${GUI_SOURCES})

# Include Qt headers automatically
target_link_libraries(xo_game
    PRIVATE
      ai
      sys
      game
      wrapper
      Qt5::Widgets
      Qt5::Core
      Qt5::Gui
      sqlite3
      # crypto or OpenSSL::Crypto as before
)

# (Optional) If you still need tests
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
