cmake_minimum_required(VERSION 3.6)
project(opt_ref)

set(CMAKE_CXX_STANDARD 17)

add_executable(opt_ref main.cpp)
add_executable(generic_proxy generic_proxy.cpp)
