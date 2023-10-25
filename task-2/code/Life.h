#ifndef CPP_LIFE_H
#define CPP_LIFE_H
#include "BitArray.h"
#include "BitArray.cpp"
#include "FileReader.h"
#include <vector>
#include <list>
#include <random>
#include <filesystem>
using std::vector;
using std::list;

class Life {
private:

    static const int STANDARD_HEIGHT = 20;
    static const int STANDARD_WIDTH = 80;
    static const int AMOUNT_PRESETS = 5;
    const list<int> STANDARD_BIRTH_RULE = {3};
    const list<int> STANDARD_SURVIVE_RULE = {2, 3};
    const string STANDARD_UNIVERSE_NAME = "My Universe";

    vector<BitArray<char>> field;
    int width;
    int height;
    int alive;
    int currGenerationNumber;

    string name;
    list<int> birthRule;
    list<int> surviveRule;
    FileReader *reader;

    static string getPresetName();

    static void showWarning(const string &msg);

    static int getInd(int ind, int mod) ;

    /**
     * read game info from file, handle errors
     * @param fileName
     */
    void create(const string &fileName);

    int getAmountNeighbours(int i, int j) const;

public:

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    explicit Life(int width, int height, const string &fileName);

    explicit Life(int width, int height);

    Life() : Life(STANDARD_WIDTH, STANDARD_HEIGHT) {}

    explicit Life(const string &fileName) : Life(STANDARD_WIDTH, STANDARD_HEIGHT, fileName) {}

    void clear();

    int getAmountAlive() const;

    Life &nextGeneration();

    int getGenNumber() const {
        return this->currGenerationNumber;
    }

    const BitArray<char> &operator[](int i);

    list<pair<int, int>> getLiveCoords() const;

    string getBirthSurviveRules() const;

    string getUniverseName() const;

    void show() const;

    void showInfo() const;

    ~Life() {
        if (reader->isOpen()) {
            reader->close();
        }
        delete reader;
    }
};

#endif //CPP_LIFE_H
