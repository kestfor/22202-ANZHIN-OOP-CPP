#include <gtest/gtest.h>
#include "FileWriter.h"
#include <fstream>

TEST(FileWriter, writeLine1) {
    string line = "test";
    FileWriter writer("test.txt");
    writer.open();
    writer.writeLine(line);
    ifstream file("test.txt");
    string res;
    file >> res;
    EXPECT_EQ(res, line);
}

TEST(FileWriter, writeLine2) {
    vector<string> lines = {"test1", "test2"};
    FileWriter writer("test.txt");
    writer.open();
    writer.writeLine(lines);
    ifstream file("test.txt");
    vector<string> res;
    while (!file.eof()) {
        string line;
        file >> line;
        if (!line.empty()) {
            res.push_back(line);
        }
    }
    EXPECT_EQ(res, lines);
}