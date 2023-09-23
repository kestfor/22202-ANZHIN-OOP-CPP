#include <list>
#include <map>
#include <algorithm>
#include <vector>
#include <clocale>
#include "FileReader.h"
#include "FileWriter.h"
#include "Parser.h"
#include <iostream>
#include "Statistics.h"
using namespace std;

bool cmp(pair<string, int> &first, pair<string, int> &second) {
    return first.second > second.second || (first.second == second.second && first.first < second.first);
}

vector<pair<string, int>> sortMapByKey(map<string, int> &container) {
    vector<pair<string, int>> array;
    for (const auto &item : container) {
        array.emplace_back(item);
    }
    sort(array.begin(), array.end(), cmp);
    return array;
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "RUS");
    if (argc != 3) {
        return 0;
    }
    string nameFrom = string(argv[1]);
    string nameTo = string(argv[2]);
    size_t totalAmount = 0;
    Statistics stat;
    FileReader reader(nameFrom);
    reader.open();
    if (!reader.isOpen()) {
        return EXIT_FAILURE;
    }
    while (reader.hasNext()) {
        string line = reader.next();
        auto words = Parser::split(line);
        totalAmount += words.size();
        for (const auto& word : words) {
            stat.add(word);
        }
    }
    reader.close();
    auto sorted = sortMapByKey(stat.getData());
    FileWriter writer(nameTo);
    writer.open();
    if (!writer.isOpen()) {
        return EXIT_FAILURE;
    }
    for (const auto &item : sorted) {
        string line = item.first + "\t" + to_string((long double) item.second / totalAmount);
        writer.writeLine(line);
    }
    writer.close();
}