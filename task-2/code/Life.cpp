#include "Life.h"


const BitArray<char> &Life::operator[](int i) {
    return this->field[i];
}

int Life::getAmountNeighbours(int i, int j) const {
    int res = 0;
    for (int k = i - 1; k <= i + 1; k++) {
        for (int l = j - 1; l <= j + 1; l++) {
            if (k != i || l != j) {
                if (field[getInd(k, height)].get(getInd(l, width))) {
                    res += 1;
                }
            }
        }
    }
    return res;
}

int Life::getInd(int ind, int mod) {
    if (ind < 0 || ind >= mod) {
        if (ind < 0) {
            return (mod + ind);
        } else {
            return ind % mod;
        }
    } else {
        return ind;
    }
}

Life &Life::nextGeneration() {
    vector<BitArray<char>> copy(height);
    alive = 0;
    for (int i = 0; i < height; i++) {
        copy[i].resize(width);
        for (int j = 0; j < width; j++) {
            int neighbours = getAmountNeighbours(i, j);
            if (field[i].get(j)){
                bool flag = false;
                for (const int &item : surviveRule) {
                    if (item == neighbours) {
                        copy[i].set(j, true);
                        alive++;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    copy[i].set(j, false);
                }
            } else {
                bool flag = false;
                for (const int  &item : birthRule) {
                    if (item == neighbours) {
                        copy[i].set(j, true);
                        alive++;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    copy[i].set(j, false);
                }
            }
        }
    }
    for (int i = 0; i < height; i++) {
        field[i] = copy[i];
    }
    currGenerationNumber++;
    return *this;
}

int Life::getAmountAlive() const {
    return alive;
}

Life::Life(LifeSettings &settings) {
    if (width < 0 || height < 0) {
        throw std::range_error("invalid field size");
    }
    this->width = settings.getWidth();
    this->height = settings.getHeight();
    this->surviveRule = settings.getSurviveRule();
    this->birthRule = settings.getBirthRule();
    this->name = settings.getName();
    this->alive = 0;
    this->currGenerationNumber = 0;
    this->field = vector<BitArray<char>>(height);
    for (int i = 0; i < height; i++) {
        this->field[i] = BitArray<char>(width);
        this->field[i].reset();
    }
    list<std::pair<int, int>> coords = settings.getCoords();
    for (const auto &item : coords) {
        field[getInd(item.first, height)].set(getInd(item.second, width), true);
        this->alive++;
    }
}

list<pair<int, int>> Life::getLiveCoords() const {
    list<pair<int, int>> coords;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (this->field[i].get(j)) {
                coords.emplace_back(i, j);
            }
        }
    }
    return coords;
}

string Life::getBirthSurviveRules() const {
    string res = "B";
    for (const auto &item : birthRule) {
        res += std::to_string(item);
    }
    res += "/S";
    for (const auto &item : surviveRule) {
        res += std::to_string(item);
    }
    return res;
}

string Life::getUniverseName() const {
    return this->name;
}

void Life::showField() const {
    for (int i = 0; i < height; i++) {
        string line;
        for (int j = 0; j < width; j++) {
            if (field[i].get(j)) {
                line.push_back('#');
            } else {
                line.push_back('.');
            }
        }
        std::cout << line << std::endl;
    }
}

void Life::showInfo() const {
    std::cout << getUniverseName() << std::endl;
    std::cout << getBirthSurviveRules() << std::endl;
    std::cout << "current gen: " << getGenNumber() << std::endl;
}
