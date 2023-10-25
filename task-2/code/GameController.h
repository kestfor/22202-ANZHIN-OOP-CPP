#ifndef CPP_GAMECONTROLLER_H
#define CPP_GAMECONTROLLER_H
#include "Life.h"
#include "CommandArgumentService.h"
#include "Command.h"

class GameController {
private:

    CommandArgumentService *arguments;
    Life *game;

protected:
    ~GameController() {
        delete arguments;
        delete game;
    }

public:

    /**
     * generate game with given commands, throw runtime error if there are argument errors
     * @param args
     * @param argv
     */
    GameController(int args, char *argv[]);

    void waitForCommand();

};

#endif //CPP_GAMECONTROLLER_H
