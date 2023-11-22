cmake_minimum_required(VERSION 3.6)
project(soundProcessor)

set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)

# Download and extract the boost library from GitHub
message(STATUS "Downloading and extracting boost library sources. This will take some time...")
include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE) # Needed to print downloading progress
FetchContent_Declare(
        Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.81.0/boost-1.81.0.7z # downloading a zip release speeds up the download
        USES_TERMINAL_DOWNLOAD TRUE
        GIT_PROGRESS TRUE
        DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(Boost)

add_executable(soundProcessor code/main.cpp
        code/WAVReader.cpp
        code/WAVReader.h
        code/WAVBase.h
        code/SampleFlow.h
        code/WAVWriter.cpp
        code/converters/Mixer.cpp
        code/converters/Converter.h
        code/converters/Muter.h
        code/converters/Muter.cpp
        code/ConfigsReader.h
        code/ConfigsReader.cpp
        code/converters/Converter.cpp
        code/converters/ConverterFactory.h
        code/Instruction.cpp
        code/Instruction.h
        code/converters/Replacer.cpp
        code/converters/Replacer.h
        code/Exceptions.h)

target_link_libraries(soundProcessor PUBLIC Boost::program_options)

enable_testing()

add_executable(
        ConfigReaderTest
        tests/ConfigReaderTest.cc
)

target_link_libraries(
        ConfigReaderTest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ConfigReaderTest)