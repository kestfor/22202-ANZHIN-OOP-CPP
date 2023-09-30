#ifndef CPP_STATISTICS_H
#define CPP_STATISTICS_H
#include <map>
#include <string>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Statistics {
private:
    map<string, int> container;

    static bool cmp(pair<string, int> &first, pair<string, int> &second) {
        return first.second > second.second || (first.second == second.second && first.first < second.first);
    }

    vector<pair<string, int>> sortMapByKey();

public:
    void add(const string &word) {
        if (container.contains(word)) {
            container[word] += 1;
        } else {
            container[word] = 1;
        }
    }

    map<string, int> &getData() {
        return container;
    }

    vector<pair<string, int>> getSortedData() {
        return this->sortMapByKey();
    }
};


#endif //CPP_STATISTICS_H
