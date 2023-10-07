#include <gtest/gtest.h>
#include "Parser.h"
#include "Parser.cpp"
#include <list>
using std::string;
using std::list;

TEST(Parser, 1) {
    string line = "a, a, a, a";
    auto words = Parser::split(line);
    list<string> res = {"a", "a", "a", "a"};
    EXPECT_EQ(words.size(), 4);
    EXPECT_EQ(res, words);
}

TEST(Parser, 2) {
    string line = "a, b/ c. d";
    auto words = Parser::split(line);
    list<string> res = {"a", "b", "c", "d"};
    EXPECT_EQ(words.size(), 4);
    EXPECT_EQ(words, res);
}

TEST(Parser, 3) {
    string line = " ";
    auto words = Parser::split(line);
    list<string> res = {};
    EXPECT_EQ(words.size(), 0);
    EXPECT_EQ(words, res);
}

TEST(Parser, 4) {
    string line = "..|/,<>";
    auto words = Parser::split(line);
    list<string> res = {};
    EXPECT_EQ(words.size(), 0);
    EXPECT_EQ(words, res);
}

TEST(Parser, 5) {
    string line = "a..|/,<d>d";
    auto words = Parser::split(line);
    list<string> res = {"a", "d", "d"};
    EXPECT_EQ(words.size(), 3);
    EXPECT_EQ(words, res);
}

TEST(Parser, 6) {
    string line = "aaa..|/,<d>dd";
    auto words = Parser::split(line);
    list<string> res = {"aaa", "d", "dd"};
    EXPECT_EQ(words.size(), 3);
    EXPECT_EQ(words, res);
}

TEST(Parser, 7) {
    string line = "aaa..|/,<d>dd,\n";
    auto words = Parser::split(line);
    list<string> res = {"aaa", "d", "dd"};
    EXPECT_EQ(words.size(), 3);
    EXPECT_EQ(words, res);
}

TEST(Parser, 8) {
    string line = "d..\t|\r/,<d>d,\n";
    auto words = Parser::split(line);
    list<string> res = {"d", "d", "d"};
    EXPECT_EQ(words.size(), 3);
    EXPECT_EQ(words, res);
}

TEST(Parser, 9) {
    string line = "";
    auto words = Parser::split(line);
    list<string> res = {};
    EXPECT_EQ(words.size(), 0);
    EXPECT_EQ(words, res);
}