cmake_minimum_required(VERSION 3.17)
project(numberWithUnits)

set(CMAKE_CXX_STANDARD 20)

set(SourceList NumberWithUnits.hpp NumberWithUnits.cpp wdgraph.hpp)

add_executable(main main.cpp ${SourceList})
add_executable(demo Demo.cpp ${SourceList})
add_executable(Temp TestRunner.cpp StudentTest1.cpp ${SourceList})

