cmake_minimum_required(VERSION 3.9)
project(utility_cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(utility_cpp
        src/array.cpp
        src/clock.cpp
        src/complexmatrix.cpp
        src/complexnumber.cpp
        src/parser.cpp
        src/randomnumbergenerator.cpp
        src/realmatrix.cpp
        src/units.cpp
        src/utility.cpp)
