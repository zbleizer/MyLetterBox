cmake_minimum_required(VERSION 3.20)
project(MyLetterBox)

set(CMAKE_CXX_STANDARD 23)

add_executable(MyLetterBox
        includeh/Model.h
        includeh/Data.h
        includeh/User.h
        src/main.cpp
        src/Model.cpp
        src/Data.cpp
        src/User.cpp
)

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

target_link_libraries(Tests gtest_main)