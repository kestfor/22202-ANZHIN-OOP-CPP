#include <iostream>
#include "../FileReader.h"
#include "../FileReader.cpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <fstream>

TEST(FileReader, nameGetter) {
    std::ofstream file("test.txt");
    file << "#Life 1.06\n#N My universe";
    file.close();
    auto fileReader = FileReader("test.txt");
    EXPECT_EQ("My universe", fileReader.getUniverseName());
    EXPECT_EQ("My universe", fileReader.getUniverseName());
}

TEST(FileReader, rulesGetter) {
    std::ofstream file("test.txt");
    file << "#Life 1.06\n#N My universe'\n#R B3/S23";
    file.close();
    auto fileReader = FileReader("test.txt");
    fileReader.getUniverseName();
    pair<list<int>, list<int>> rules = fileReader.getBirthSurviveRules();
    list<int> res1 = {3};
    list<int> res2 = {2, 3};
    EXPECT_EQ(res1, rules.first);
    EXPECT_EQ(res2, rules.second);
}

TEST(FileReader, formatException) {
    std::ofstream file("test.txt");
    file << "1";
    file.close();
    FileReader reader;
    try {
        reader.open("test.txt");
    } catch (const std::runtime_error &err) {
        EXPECT_STREQ("file not in Life 1.06 format", err.what());
    }
}

TEST(FileReader, nameException) {
    std::ofstream file("test.txt");
    file << "#Life 1.06\n#R B3/S23";
    file.close();
    FileReader reader("test.txt");
    try {
        reader.getUniverseName();
    } catch (const std::runtime_error &err) {
        EXPECT_STREQ("file does not contain universe name", err.what());
        pair<list<int>, list<int>> rules = reader.getBirthSurviveRules();
        list<int> res1 = {3};
        list<int> res2 = {2, 3};
        EXPECT_EQ(res1, rules.first);
        EXPECT_EQ(res2, rules.second);
    }
}

TEST(FileReader, ruleException) {
    std::ofstream file("test.txt");
    file << "#Life 1.06\n1 0";
    file.close();
    FileReader reader("test.txt");
    try {
        reader.getUniverseName();
    } catch (const std::runtime_error &err) {
        EXPECT_STREQ("file does not contain universe name", err.what());
    }
    try {
        reader.getBirthSurviveRules();
    } catch (const std::runtime_error &err) {
        EXPECT_STREQ("file does not contain transition rules", err.what());
    }
}

TEST(FileReader, ruleFormatException) {
    std::ofstream file("test.txt");
    file << "#Life 1.06\n#N My universe'\n#R B3S23";
    file.close();
    FileReader reader("test.txt");
    reader.getUniverseName();
    try {
        reader.getBirthSurviveRules();
    } catch (const std::runtime_error &err) {
        EXPECT_STREQ("format error", err.what());
    }
}

TEST(FileReader, coords) {
    std::ofstream file("test.txt");
    file << "#Life 1.06\n#N My universe'\n#R B3/S23\n1 0\n1 1\n0 1";
    file.close();
    FileReader reader("test.txt");
    auto coords = reader.readCoords();
    list<pair<int, int>> res = {{1, 0}, {1, 1}, {0, 1}};
    EXPECT_EQ(res, coords);
    EXPECT_EQ(res, reader.readCoords());
}

