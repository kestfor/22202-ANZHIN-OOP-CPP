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
    map<string, string> allowedArgs = {{"-f", ""}, {"--file=", ""},
                                       {"-i", ""}, {"--iterations=", ""},
                                       {"-o", ""}, {"--output=", ""}};

    static void handleWrongArguments();

public:

    static vector<string> parseCommand(const string &line);

    map<string, string> parseArguments(int args, char *argv[]);

};

#endif //CPP_COMMANDARGUMENTSERVICE_H
