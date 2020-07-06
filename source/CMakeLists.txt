cmake_minimum_required(VERSION 3.16)
project(source)

set(CMAKE_CXX_STANDARD 17)

add_executable(source main.cpp token.h token.cpp condition_parser.h condition_parser.cpp condition_parser_test.cpp)