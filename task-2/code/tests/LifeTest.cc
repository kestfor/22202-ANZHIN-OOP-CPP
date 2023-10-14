#include <iostream>
#include "gtest/gtest.h"
#include "../BitArray.h"
#include "../FileReader.cpp"
#include "../Life.cpp"


TEST(Life, constructor) {
    string fileName = "C:/study/oop/cpp/task-2/presets/1.life";
    Life life(fileName);
    EXPECT_EQ(5, life.getAmountAlive());
}

TEST(Life, rules) {
    string fileName = "C:/study/oop/cpp/task-2/presets/1.life";
    Life life(fileName);
    auto rules = life.getBirthSurviveRules();
    string res = "B3/S23";
    EXPECT_EQ(res, rules);
}

TEST(Life, name) {
    string fileName = "C:/study/oop/cpp/task-2/presets/1.life";
    Life life(fileName);
    auto rules = life.getUniverseName();
    string res = "My Universe";
    EXPECT_EQ(res, rules);
}

