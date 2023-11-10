#ifndef CPP_COMMANDARGUMENTSERVICE_H
#define CPP_COMMANDARGUMENTSERVICE_H
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
using std::vector;
using std::map;
using std::string;

class CommandArgumentService {
private:
    static void handleWrongArguments();

public:

    enum allowedShortArgs {
        f,
        i,
        o,
        file,
        iterations,
        output,
    };

    static vector<string> parseCommand(const string &line);

    static map<string, string> parseArguments(int args, char *argv[]);

};

#endif //CPP_COMMANDARGUMENTSERVICE_H
