cmake_minimum_required(VERSION 3.17)
project(numberWithUnits)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)
add_executable(numberWithUnits NumberWithUnits.hpp Demo.cpp )
add_executable(Ts NumberWithUnits.hpp NumberWithUnits.cpp Test.cpp )