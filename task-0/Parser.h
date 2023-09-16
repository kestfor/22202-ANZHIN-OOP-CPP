#ifndef CPP_PARSER_H
#define CPP_PARSER_H
#include <string>
#include <list>

using namespace std;

class Parser {
private:

    static bool isDelimiter(unsigned char alpha) {
        return not(isalpha(alpha) || isdigit(alpha));
    }

public:
    static list<string> split(string &line);
};

#endif //CPP_PARSER_H
