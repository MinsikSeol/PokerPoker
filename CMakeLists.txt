cmake_minimum_required(VERSION 3.21)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(untitled2 main/main.cpp test.cpp main/cardCompare.h main/sampleTest.cpp
		main/simulation_ccExecution.cpp)
