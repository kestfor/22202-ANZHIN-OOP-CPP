#ifndef CPP_STATISTICS_H
#define CPP_STATISTICS_H
#include <map>
#include <string>
using std::map;
using std::string;

class Statistics {
private:
    map<string, int> container;

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
};


#endif //CPP_STATISTICS_H
