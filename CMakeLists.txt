cmake_minimum_required(VERSION 3.17)
project(numberWithUnits)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)
add_executable(numberWithUnits NumberWithUnits.hpp Demo.cpp NodeData.hpp NodeData.cpp WDGraph.hpp WDGraph.cpp )
add_executable(nn NumberWithUnits.hpp main.cpp NodeData.hpp NodeData.cpp WDGraph.hpp WDGraph.cpp NumberWithUnits.cpp)
