cmake_minimum_required(VERSION 3.10)
project(BoostSml)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.63 REQUIRED COMPONENTS)

add_subdirectory(Sml)
include_directories(Sml/include)

# Disable GoogleTest for the time being
# add_subdirectory(googletest)
# include_directories(googletest/googletest/include googletest/googletest)
# include_directories(googletest/googlemock/include googletest/googlemock)

add_executable(SmlHelloWorld sml_hello_world.cpp)

# enable_testing()

# add_executable(UnitTest unit-tests.cpp)
# target_link_libraries(UnitTest gtest gtest_main)