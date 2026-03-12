cmake_minimum_required(VERSION 4.0)
project(MyLetterBox)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(MyLetterBox src/main.cpp
        includeh/Model.h
        includeh/Data.h
        includeh/User.h
        src/Model.cpp
        src/Data.cpp)
add_executable(Tests tests/tests.cpp)
target_link_libraries(Tests gtest_main)
