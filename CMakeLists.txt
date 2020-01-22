cmake_minimum_required(VERSION 3.15)
project(cwushell)

set(CMAKE_CXX_STANDARD 14)

add_executable(cwushell driver.cpp cwushell.cpp cwushell.h)