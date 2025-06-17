cmake_minimum_required(VERSION 3.16)

project(Tic_Tac_Toe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Library Paths ---

# Manually specify the paths for OpenSSL
set(OPENSSL_INCLUDE_DIR "C:/vcpkg/packages/openssl_x64-windows/include")
set(OPENSSL_CRYPTO_LIBRARY "C:/vcpkg/packages/openssl_x64-windows/lib/libcrypto.lib")
set(OPENSSL_SSL_LIBRARY "C:/vcpkg/packages/openssl_x64-windows/lib/libssl.lib")

# Manually specify the paths for SQLite3
set(SQLITE3_INCLUDE_DIR "C:/vcpkg/packages/sqlite3_x64-windows/include")
set(SQLITE3_LIBRARY "C:/vcpkg/packages/sqlite3_x64-windows/lib/sqlite3.lib")

# --- Find Qt ---

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        signup.h
        signup.cpp
        signup.ui
        mainscreen.h
        mainscreen.cpp
        mainscreen.ui
        turnpage.h
        turnpage.cpp
        turnpage.ui
        aipage.h
        aipage.cpp
        aipage.ui
        gameboard.h
        gameboard.cpp
        gameboard.ui
        history.h
        history.cpp
        history.ui
        game_wrapper.h
        game_wrapper.cpp
        user_system.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Tic_Tac_Toe
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        signup.h signup.cpp signup.ui
        mainscreen.h mainscreen.cpp mainscreen.ui
        GameData.h
        turnpage.h turnpage.cpp turnpage.ui
        aipage.h aipage.cpp aipage.ui
        gameboard.h gameboard.cpp gameboard.ui
        history.h history.cpp history.ui
        ai.cpp ai.h game_logic.h game_wrapper.cpp user_system.cpp user_system.h
        # ai.cpp
        game_wrapper.cpp
        game_wrapper.h
        GameData.cpp
        game_logic.h
        game_logic.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Tic_Tac_Toe APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Tic_Tac_Toe SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Tic_Tac_Toe
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Add the include directories for all external libraries
target_include_directories(Tic_Tac_Toe PRIVATE
    ${OPENSSL_INCLUDE_DIR}
    ${SQLITE3_INCLUDE_DIR}
)

target_link_libraries(Tic_Tac_Toe PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
  ${OPENSSL_SSL_LIBRARY}
      ${OPENSSL_CRYPTO_LIBRARY}
      ${SQLITE3_LIBRARY})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Tic_Tac_Toe)
endif()
set_target_properties(Tic_Tac_Toe PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Tic_Tac_Toe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Tic_Tac_Toe)
endif()
