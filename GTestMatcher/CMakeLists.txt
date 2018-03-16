cmake_minimum_required(VERSION 3.10)
project(SimpleGTest)

set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.63 REQUIRED COMPONENTS)

add_subdirectory(googletest)
include_directories(googletest/googletest/include googletest/googletest)
include_directories(googletest/googlemock/include googletest/googlemock)

enable_testing()

add_executable(GTestMatcher unit-tests.cpp)
target_link_libraries(GTestMatcher gtest gtest_main)