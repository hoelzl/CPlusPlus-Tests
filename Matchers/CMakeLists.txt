cmake_minimum_required(VERSION 3.6)
project(simple_project)

set(CMAKE_CXX_STANDARD 14)

add_library(approximate lib.cpp)

add_executable(matchers main.cpp)
target_link_libraries(matchers approximate)

enable_testing()

add_subdirectory(googletest)
include_directories(googletest/googletest/include googletest/googletest)
include_directories(googletest/googlemock/include googletest/googlemock)

add_executable(unit_tests unit_tests.cpp)
target_link_libraries(unit_tests approximate gtest gtest_main)
