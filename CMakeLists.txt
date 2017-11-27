cmake_minimum_required(VERSION 3.6)
project(gcpp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES  foo.c foo.h main.cpp Customer.cpp Customer.h)
add_executable(maincpp ${SOURCE_FILES})