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

    inline static map<string , string> allowedArgs = {{"-f", ""}, {"--file=", ""},
                                                      {"-i", ""}, {"--iterations=", ""},
                                                      {"-o", ""}, {"--output=", ""}};
public:

    static vector<string> parseCommand(const string &line);

    static map<string, string> parseArguments(int args, char *argv[]);

};

#endif //CPP_COMMANDARGUMENTSERVICE_H
