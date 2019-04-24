cmake_minimum_required(VERSION 3.12)
project(parallel_programming)

set(CMAKE_CXX_STANDARD 14)

set(INC_DIR "E:\\download\\chrome\\Microsoft-MPI-master\\Microsoft-MPI-master\\src\\include")
#set(LINK_DIR D://Program Files//Microsoft MPI)

#添加头文件搜索路径
include_directories(${INC_DIR})
#添加库文件搜索路径
link_directories(${LINK_DIR})


set(CMAKE_CXX_COMPILER mpicxx)
set(CMAKE_C_COMPILER mpicc)
find_package(MPI REQUIRED)

add_executable(parallel_programming main.cpp)
target_include_directories(parallel_programming PUBLIC INC_DIR)
