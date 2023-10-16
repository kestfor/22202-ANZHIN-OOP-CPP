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

    /**
     * saves current field of game to the file
     * @param fileName
     * @param waitForCommand wait another command after this one if its true
     */
    void dumpToFile(const string &fileName, bool waitForCommand = true);

    /**
     * show game field after n ticks with game info
     * @param n
     * @param waitForCommand wait another command after this one if its true
     */
    void getTick(int n = 1, bool waitForCommand = true);

    /**
     * show info about available commands
     * @param waitForCommand wait another command after this one if its true
     */
    void help(bool waitForCommand = true);

    /**
     * run game in real-time for n ticks
     * @param n
     */
    void live(int n=50);

    /**
     * finish game
     */
    void exit();

    static void handleWrongCommand(const string &cmd);

    static void handleWrongArguments();

public:

    int getGameMode() const {
        return mode;
    }

    enum gameMode {
        online,
        offline
    };

    /**
     * Interface constructor, it parses arguments, sets game mode, throw runtime_error if there are argument errors
     * @param args amount of command line arguments
     * @param argv command line arguments
     */
    UserInterface(int args, char *argv[]);

    /**
     * initialize game of life with given to constructor arguments
     */
    void gameInit();

    /**
     * wait for command to read from cin, handle wrong commands, generate infinite loop until command 'exit' is called
     */
    void waitForCommand();

    ~UserInterface() {
        delete game;
    }

};

#endif //CPP_USERINTERFACE_H