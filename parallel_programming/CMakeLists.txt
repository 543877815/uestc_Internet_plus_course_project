cmake_minimum_required(VERSION 3.12)
project(parallel_programming)

set(CMAKE_CXX_STANDARD 14)

set(INC_DIR D://MPI//Include//)
set(LINK_DIR D://MPI//Lib//x64//)

#添加头文件搜索路径
include_directories(${INC_DIR})
#添加库文件搜索路径
link_directories(${LINK_DIR})

add_executable(parallel_programming main.cpp)
