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

    CommandArgumentService(int args, char *argv[]);

    const string &getArgument(const string &name);

    bool contains(const string &name);

    const string &operator[](const string &name);

};

#endif //CPP_COMMANDARGUMENTSERVICE_H
