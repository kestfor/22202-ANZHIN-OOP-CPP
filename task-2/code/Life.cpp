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

void Life::clear() {
    this->alive = 0;
    for (int i = 0; i < height; i++) {
        this->field[i].reset();
    }
}

Life::Life(int width, int height, const string &fileName) {
    if (width > 0 && height > 0) {
        this->width = width;
        this->height = height;
        this->alive = 0;
        this->currGenerationNumber = 0;
    } else {
        throw std::range_error("invalid field size");
    }
    create(fileName);
}

Life::Life(int width, int height) {
    if (width > 0 && height > 0) {
        this->width = width;
        this->height = height;
        this->alive = 0;
        this->currGenerationNumber = 0;
    } else {
        throw std::range_error("invalid field size");
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1,AMOUNT_PRESETS);
    string presetName = std::filesystem::current_path().string() + "\\..\\presets\\" + to_string(dist(gen)) + ".life";
    create(presetName);
}

void Life::create(const string &fileName) {
    try {
        reader = new FileReader(fileName);
    } catch (const runtime_error &err) {
        showWarning(err.what());
    }
    try {
        name = reader->getUniverseName();
    } catch (const runtime_error &err) {
        showWarning(err.what());
        name = "My universe";
    }
    try {
        auto rules = reader->getBirthSurviveRules();
        birthRule = rules.first;
        surviveRule = rules.second;
    } catch (const runtime_error &err) {
        showWarning(err.what());
        birthRule = {3};
        surviveRule = {2, 3};
    }
    this->field = vector<BitArray<char>>(height);
    for (int i = 0; i < height; i++) {
        this->field[i] = BitArray<char>(width);
        this->field[i].reset();
    }
    list<pair<int, int>> coords = reader->readCoords();
    for (const auto &item : coords) {
        field[getInd(item.first, height)].set(getInd(item.second, width), true);
        this->alive++;
    }
    reader->close();
}

void Life::showWarning(const string &msg) {
    cout << msg << endl;
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
        res += to_string(item);
    }
    res += "/S";
    for (const auto &item : surviveRule) {
        res += to_string(item);
    }
    return res;
}

string Life::getUniverseName() const {
    return this->name;
}

void Life::show() const {
    for (int i = 0; i < height; i++) {
        string line;
        for (int j = 0; j < width; j++) {
            if (field[i].get(j)) {
                line.push_back('#');
            } else {
                line.push_back('.');
            }
        }
        cout << line << endl;
    }
}
