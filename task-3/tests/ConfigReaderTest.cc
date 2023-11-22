#include <gtest/gtest.h>
#include "../code/ConfigsReader.h"
#include "../code/ConfigsReader.cpp"
#include <fstream>


TEST(ConfigReader, readline) {
    std::ofstream file("test.txt");
    const std::string text = "#comment\n"
                       "mute 10 20\n"
                       "#comment2\n"
                       "mix $2 10";
    file << text;
    file.close();
    const ConfigsReader configReader("test.txt");
    const string line1 = configReader.readline();
    const string line2 = configReader.readline();
    EXPECT_EQ(line1, "mute 10 20");
    EXPECT_EQ(line2, "mix $2 10");
}