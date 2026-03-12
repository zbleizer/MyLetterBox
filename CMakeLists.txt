cmake_minimum_required(VERSION 3.20)
project(MyLetterBox)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        src/main.cpp
        src/Model.cpp
        src/Data.cpp
        src/User.cpp
)

set(HEADERS
        includeh/Model.h
        includeh/Data.h
        includeh/User.h
)

add_executable(MyLetterBox ${SOURCES} ${HEADERS})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Tests
        tests/tests.cpp
        src/Model.cpp
        src/Data.cpp
        src/User.cpp
)

target_include_directories(Tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includeh
)

target_link_libraries(Tests
        PRIVATE
        gtest_main
        gtest
)
target_include_directories(MyLetterBox PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includeh
)