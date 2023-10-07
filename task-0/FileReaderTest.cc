#include <gtest/gtest.h>
#include <fstream>
#include "FileReader.h"
using namespace std;

TEST(FileReader, next) {
    ofstream file("test.txt");
    file << "test";
    file.close();
    FileReader reader("test.txt");
    reader.open();
    string line = reader.next();
    EXPECT_EQ("test", line);
}

TEST(FileReader, hasNext) {
    ofstream file("test.txt");
    file << "test";
    file.close();
    FileReader reader("test.txt");
    reader.open();
    reader.next();
    EXPECT_EQ(false, reader.hasNext());
}

TEST(FileReader, reset) {
    ofstream file("test.txt");
    file << "test";
    file.close();
    FileReader reader("test.txt");
    reader.open();
    reader.next();
    reader.reset();
    EXPECT_EQ("test", reader.next());
}

TEST(FileReader, isOpen) {
    FileReader reader("test.txt");
    EXPECT_EQ(false, reader.isOpen());
}
