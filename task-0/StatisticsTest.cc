#include <gtest/gtest.h>
#include "Statistics.h"
#include <map>
#include <vector>
#include <utility>
using namespace std;

TEST(Statistics, 1) {
    vector<string> words = {"a", "a", "a", "b"};
    Statistics stat;
    for (auto const &word : words) {
        stat.add(word);
    }
    map<string, int> res = {{"a", 3}, {"b", 1}};
    EXPECT_EQ(res, stat.getData());
}

TEST(Statistics, 2) {
    vector<string> words = {"a", "b", "c", "d"};
    Statistics stat;
    for (auto const &word : words) {
        stat.add(word);
    }
    map<string, int> res = {{"a", 1}, {"b", 1}, {"c", 1}, {"d", 1}};
    EXPECT_EQ(res, stat.getData());
}
