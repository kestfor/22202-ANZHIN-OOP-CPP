cmake_minimum_required(VERSION 3.26)
project(cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp FileReader.h Parser.h Parser.cpp FileWriter.h
        Statistics.h Statistics.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()


add_executable(
        StatisticsTest
        StatisticsTest.cc
)

add_executable(
        ParserTest
        ParserTest.cc
)

add_executable(
        FileReaderTest
        FileReaderTest.cc
)

add_executable(
        FileWriter
        FileWriter.cc
)

target_link_libraries(
        StatisticsTest
        GTest::gtest_main
)

target_link_libraries(
        ParserTest
        GTest::gtest_main
)

target_link_libraries(
        FileReaderTest
        GTest::gtest_main
)

target_link_libraries(
        FileWriter
        GTest::gtest_main
)


include(GoogleTest)
gtest_discover_tests(StatisticsTest ParserTest FileReaderTest FileWriter)

