cmake_minimum_required(VERSION 3.12)
project(parallel_programming)

set(CMAKE_CXX_STANDARD 14)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

set(CMAKE_CXX_COMPILER mpicxx)
set(CMAKE_C_COMPILER mpicc)

add_executable(main main3.cpp)
