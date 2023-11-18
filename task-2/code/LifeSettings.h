#ifndef CPP_LIFESETTINGS_H
#define CPP_LIFESETTINGS_H
#include <iostream>
#include <list>
#include <utility>
using std::pair;

class LifeSettings {
protected:
    const int STANDARD_HEIGHT = 20;
    const int STANDARD_WIDTH = 80;
    const std::list<int> STANDARD_BIRTH_RULE = {3};
    const std::list<int> STANDARD_SURVIVE_RULE = {2, 3};
    const std::string STANDARD_UNIVERSE_NAME = "My Universe";

    int width;
    int height;
    std::string name;
    std::list<int> birthRule;
    std::list<int> surviveRule;
    std::list<pair<int, int>> startCoords;

public:
    LifeSettings() {
        width = STANDARD_WIDTH;
        height = STANDARD_HEIGHT;
        name = STANDARD_UNIVERSE_NAME;
        birthRule = STANDARD_BIRTH_RULE;
        surviveRule = STANDARD_SURVIVE_RULE;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    std::string getName() const {
        return name;
    }

    std::list<int> getBirthRule() const {
        return birthRule;
    }

    std::list<int> getSurviveRule() const {
        return surviveRule;
    }

    std::list<pair<int, int>> getCoords() const {
        return startCoords;
    }

    void setWidth(int w) {
        width = w;
    }

    void setHeight(int h) {
        height = h;
    }

    void setName(const std::string &name) {
        this->name = name;
    }

    void setBirthRule(const std::list<int> &rule) {
        birthRule = rule;
    }

    void setSurviveRule(const std::list<int> &rule) {
        surviveRule = rule;
    }

    void setBirthSurviveRules(const std::pair<std::list<int>, std::list<int>> rules) {
        birthRule = rules.first;
        surviveRule = rules.second;
    }

    void setStartCoords(const std::list<pair<int, int>> coords) {
        startCoords = coords;
    }

};

#endif //CPP_LIFESETTINGS_H
