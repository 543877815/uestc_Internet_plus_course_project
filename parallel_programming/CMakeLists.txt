cmake_minimum_required(VERSION 3.12)
project(parallel_programming)

set(CMAKE_CXX_STANDARD 14)

<<<<<<< HEAD
set(INC_DIR D://MPI//Include//)
set(LINK_DIR D://MPI//Lib//x64//)
=======
>>>>>>> 5dfafda82c3bea527b03912fd7990bfaecad9509

find_package(MPI REQUIRED)

<<<<<<< HEAD
add_executable(parallel_programming main.cpp)
=======
include_directories(${MPI_INCLUDE_PATH})

set(CMAKE_CXX_COMPILER mpicxx)
set(CMAKE_C_COMPILER mpicc)

add_executable(parallel_programming main.cpp)

>>>>>>> 5dfafda82c3bea527b03912fd7990bfaecad9509
