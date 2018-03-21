cmake_minimum_required(VERSION 3.10)
project(SimpleGTest)

set(CMAKE_CXX_STANDARD 14)

# set(CMAKE_CXX_LINK_EXECUTABLE "gold <LINK_LIBRARIES> <OBJECTS>")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.63 REQUIRED COMPONENTS)

add_subdirectory(googletest)
include_directories(googletest/googletest/include googletest/googletest)
include_directories(googletest/googlemock/include googletest/googlemock)

enable_testing()

add_executable(OdrViolation unit-tests-1.cpp unit-tests-2.cpp)
target_link_libraries(OdrViolation -flto -Wodr)
target_link_libraries(OdrViolation gtest gtest_main)