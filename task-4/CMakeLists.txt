cmake_minimum_required(VERSION 3.6)
project(CSVParser)

set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp CSVParser.h CSVParser.cpp Exceptions.h)
