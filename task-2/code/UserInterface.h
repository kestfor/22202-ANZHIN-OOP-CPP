#ifndef CPP_USERINTERFACE_H
#define CPP_USERINTERFACE_H
#include <windows.h>
#include "Life.h"
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include <map>
using namespace std;

class UserInterface {
private:

    vector<string> allowedCmds = {"dump", "tick", "t", "exit", "help", "live"};
    map<string, string> allowedArgs = {{"-f", ""}, {"--file=", ""},
                                       {"-i", ""}, {"--iterations=", ""},
                                       {"-o", ""}, {"--output=", ""}};
    int mode;
    Life *game = nullptr;

    void dumpToFile(const string &fileName, bool waitForCommand = true);

    void getTick(int n = 1, bool waitForCommand = true);

    void help(bool waitForCommand = true);

    void live(int n=50);

    void exit();

    static void handleWrongCommand(const string &cmd);

    static void handleWrongArguments();

    static void showWarning(const string &msg);

public:

    int getGameMode() const {
        return mode;
    }

    enum gameMode {
        online,
        offline
    };

    UserInterface(int args, char *argv[]);

    void gameInit();

    void waitForCommand();

    void stop();

    ~UserInterface() {
        delete game;
    }

};

#endif //CPP_USERINTERFACE_H
