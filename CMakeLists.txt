cmake_minimum_required(VERSION 3.13)
project(Obj_5)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../build")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

add_executable(Obj_5 src/main.cpp src/main.h src/functions.cpp src/functions.h src/classes/WordModel/WordModel.h)