cmake_minimum_required(VERSION 3.26)
project(cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 23)

add_executable(main main.cpp FileReader.h Parser.h Parser.cpp FileWriter.h)
