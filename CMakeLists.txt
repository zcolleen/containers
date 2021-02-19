cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS " -std=c++98 -Wall -Wextra -Werror")

add_executable(containers main.cpp binary_tree.hpp map.hpp multimap.hpp)