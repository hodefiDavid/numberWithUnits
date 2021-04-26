cmake_minimum_required(VERSION 3.17)
project(numberWithUnits)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp NumberWithUnits.hpp NumberWithUnits.cpp)
add_executable(demo Demo.cpp NumberWithUnits.hpp NumberWithUnits.cpp)

