cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS " -std=c++98 -Wall -Wextra -Werror -o2")

add_executable(containers main.cpp list.hpp stack.hpp queue.hpp vector.hpp)