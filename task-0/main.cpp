#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <algorithm>
#include <vector>
#include <clocale>
using namespace std;

bool isDelimiter(unsigned char alpha) {
    return not(isalpha(alpha) || isdigit(alpha));
}

list<string> split(string &line) {
    list<string> result;
    if (line.empty()) {
        return result;
    }
    size_t startInd = 0;
    size_t endInd = line.size() - 1;
    while (startInd <= endInd) {
        while (startInd < endInd && isDelimiter(line[startInd])) {
            startInd++;
        }
        for (size_t i = startInd; i <= endInd; i++) {
            if (isDelimiter(line[i])) {
                result.push_back(line.substr(startInd, i - startInd));
                startInd = i + 1;
                break;
            } else if (i == endInd && !isDelimiter(line[i])) {
                result.push_back(line.substr(startInd, i - startInd + 1));
                startInd = i + 1;
            }
        }
    }
    return result;
}

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
    ifstream sourceFile(nameFrom);
    map<string, int> container;
    size_t totalAmount = 0;
    while (!sourceFile.eof()) {
        string line;
        getline(sourceFile, line);
        auto words = split(line);
        totalAmount += words.size();
        for (const auto& word : words) {
            if (container.contains(word)) {
                container[word]++;
            } else {
                container[word] = 1;
            }
        }
    }
    sourceFile.close();
    auto sorted = sortMapByKey(container);
    ofstream outputFile(nameTo);
    for (const auto &item : sorted) {
        outputFile << item.first << "\t" << (long double) item.second / totalAmount << endl;
    }
    outputFile.close();
}