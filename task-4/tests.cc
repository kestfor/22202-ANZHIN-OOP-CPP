#include <gtest/gtest.h>
#include "CSVParser.h"
#include "CSVParser.cpp"

TEST(errors, wrongSize) {
    std::ofstream file("test.csv");
    file << "1,2,3,4,5";
    file.close();
    std::ifstream from("test.csv");
    CSVParser<int, int, int, int> parser(from);
    EXPECT_ANY_THROW(
    for (const auto &item : parser) {}
    );
}

TEST(errors, unexpectedType) {
    std::ofstream file("test.csv");
    file << "1,2,3,4,string";
    file.close();
    std::ifstream from("test.csv");
    CSVParser<int, int, int, int, int> parser(from);
    EXPECT_ANY_THROW(
    for (const auto &item : parser) {}
    );
}

TEST(parsing, emptyString) {
    std::ofstream file("test.csv");
    file.close();
    std::ifstream from("test.csv");
    CSVParser<int, int, int, int, int> parser(from);
    for (const auto &item : parser) {}
}

TEST(parsing, twoStrings) {
    std::ofstream file("test.csv");
    file << "1,c,1.0\n2,g,2.0";
    file.close();
    std::ifstream from("test.csv");
    CSVParser<int, char, double> parser(from);
    std::vector<std::tuple<int, char, double>> res;
    for (const auto &item : parser) {
        res.push_back(item);
    }
    std::vector<std::tuple<int, char, double>> expected = {{1, 'c', 1.0}, {2, 'g', 2.0}};
    EXPECT_EQ(expected, res);
}

TEST(parsing, escapeChars) {
    std::ofstream file("test.csv");
    file << "\"test";
    file.close();
    std::ifstream from("test.csv");
    CSVParser<string> parser(from, 0, ',', '"');
    string res;
    for (const auto &item: parser) {
        res = std::get<0>(item);
    }
    EXPECT_EQ("\test", res);
}

TEST(parsing, separator) {
    std::ofstream file("test.csv");
    file << "123;string";
    file.close();
    std::ifstream from("test.csv");
    CSVParser<int, string> parser(from, 0, ';');
    std::tuple<int, string> expected = {123, "string"};
    for (const auto &item : parser) {
        EXPECT_EQ(expected, item);
    }
}

TEST(parsing, skipLines) {
    std::ofstream file("test.csv");
    file << "123;string\n222;string2";
    file.close();
    std::ifstream from("test.csv");
    CSVParser<int, string> parser(from, 1, ';');
    std::tuple<int, string> expected = {222, "string2"};
    for (const auto &item : parser) {
        EXPECT_EQ(expected, item);
    }
}