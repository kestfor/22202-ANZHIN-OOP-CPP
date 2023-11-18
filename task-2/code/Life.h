#ifndef CPP_LIFE_H
#define CPP_LIFE_H
#include "BitArray.h"
#include "BitArray.cpp"
#include "LifeSettings.h"
#include <vector>
#include <list>
#include <random>
#include <filesystem>
using std::vector;
using std::list;
using std::string;
using std::pair;

class Life {
private:
    vector<BitArray<char>> field;
    int width;
    int height;
    int alive;
    int currGenerationNumber;

    string name;
    list<int> birthRule;
    list<int> surviveRule;

    static int getInd(int ind, int mod) ;

    int getAmountNeighbours(int i, int j) const;

public:

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    explicit Life(LifeSettings &settings);

    int getAmountAlive() const;

    Life &nextGeneration();

    int getGenNumber() const {
        return this->currGenerationNumber;
    }

    const BitArray<char> &operator[](int i);

    list<pair<int, int>> getLiveCoords() const;

    string getBirthSurviveRules() const;

    string getUniverseName() const;

    void showField() const;

    void showInfo() const;
};

#endif //CPP_LIFE_H
