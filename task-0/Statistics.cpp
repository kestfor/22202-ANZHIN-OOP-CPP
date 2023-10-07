#include <vector>
#include <map>
#include <algorithm>
#include "Statistics.h"
using namespace std;


vector<pair<string, int>> Statistics::sortMapByKey() {
    vector<pair<string, int>> array;
    for (const auto &item : container) {
        array.emplace_back(item);
    }
    sort(array.begin(), array.end(), cmp);
    return array;
}