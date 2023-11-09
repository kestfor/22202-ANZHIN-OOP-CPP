cmake_minimum_required(VERSION 3.26)
project(cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(gameOfLife code/main.cpp code/BitArray.h code/BitArray.cpp
        code/Life.cpp
        code/Life.h
        code/FileReader.cpp
        code/FileReader.h
        code/CommandArgumentService.cpp
        code/CommandArgumentService.h
        code/GameController.cpp
        code/GameController.h
        code/commands/CommandFactory.h
)


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
        FileReaderTest
        code/tests/FileReaderTest.cc
)

add_executable(
        LifeTest
        code/tests/LifeTest.cc
)

target_link_libraries(
        FileReaderTest
        GTest::gtest_main
)

target_link_libraries(
        LifeTest
        GTest::gtest_main
)

add_executable(
        CmdArgumentServiceTest
        code/tests/CmdArgumentServiceTest.cc
)

target_link_libraries(
        CmdArgumentServiceTest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(FileReaderTest LifeTest CmdArgumentServiceTest)