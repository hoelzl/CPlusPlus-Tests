cmake_minimum_required(VERSION 3.10)
project(FunTemplate)

set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.63 REQUIRED COMPONENTS)

add_executable(FunTemplates main.cpp)
