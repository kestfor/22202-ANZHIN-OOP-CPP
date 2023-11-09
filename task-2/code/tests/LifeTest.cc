#include <iostream>
#include "gtest/gtest.h"
#include "../BitArray.h"
#include "../LifeSettings.h"
#include "../Life.cpp"


TEST(Life, constructor) {
    LifeSettings settings;
    Life life(settings);
    EXPECT_EQ(0, life.getAmountAlive());
}

TEST(Life, rules) {
    LifeSettings settings;
    settings.setBirthSurviveRules({{1, 2}, {1, 2}});
    Life life(settings);
    auto rules = life.getBirthSurviveRules();
    string res = "B12/S12";
    EXPECT_EQ(res, rules);
}

TEST(Life, name) {
    LifeSettings settings;
    settings.setName("My Universe");
    Life life(settings);
    auto rules = life.getUniverseName();
    string res = "My Universe";
    EXPECT_EQ(res, rules);
}

