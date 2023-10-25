#ifndef CPP_COMMAND_H
#define CPP_COMMAND_H
#include "Life.h"
#include <windows.h>
#include <string>
#include <map>


class Command {
private:
    enum allowedCmds {
        tick,
        dump,
        t,
        help,
        live,
        exit,
    };

    std::map<std::string, allowedCmds> allowedCmdsMap {
            {"tick", tick},
            {"dump", dump},
            {"t", t},
            {"help", help},
            {"live", live},
            {"exit", exit}
    };

    /**
     * saves current field of game to the file
     * @param fileName
     */
    void dumpToFileCmd(const string &fileName);

    /**
     * show game field after n ticks with game info
     * @param n
     */
    void getTickCmd(int n = 1, bool clearScreen = true);

    /**
     * show info about available commands
     */
    static void helpCmd();

    /**
     * run game in real-time for n ticks
     * @param n
     */
    void liveCmd(int n=50);

    /**
     * finish game
     */
    void exitCmd();


    Life *game;


public:
    explicit Command(Life *game) {
        this->game = game;
    }

    void execute(std::vector<std::string> &arguments);
};

#endif //CPP_COMMAND_H
