cmake_minimum_required(VERSION 3.16)

project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lab2
    src/main.cpp
    src/lab_string.cpp
)

target_include_directories(lab2 PRIVATE include)
target_compile_options(lab2 PRIVATE -Wall -Wextra -pedantic)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(lab2_tests
    tests/test_string.cpp
    src/lab_string.cpp
)

target_include_directories(lab2_tests PRIVATE include)
target_compile_options(lab2_tests PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(lab2_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab2_tests)
