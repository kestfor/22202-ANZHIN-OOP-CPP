#ifndef CPP_GAMECONTROLLER_H
#define CPP_GAMECONTROLLER_H
#include "Life.h"
#include "LifeSettings.h"
#include <string>
#include "CommandArgumentService.h"
#include "commands/CommandFactory.h"
#include "commands/DumpCommand.h"
#include "commands/TickCommand.h"
#include "commands/HelpCommand.h"
#include "commands/LiveCommand.h"
#include "commands/ExitCommand.h"

using std::string;

class GameController {
private:

    CommandFactory *factory;
    Life *game;

    void waitForCommand();

public:

    /**
     * generate game with given commands, throw runtime error if there are argument errors
     * @param args
     * @param argv
     */
    explicit GameController(LifeSettings &settings);

    /**
     * run game in offline mode
     * @param amountTicks
     * @param file
     */
    void runGame(const string &amountTicks, const string &file);

    /**
     * run game in online mode, generate infinite loop until command exit
     */
    void runGame();

    ~GameController() {
        delete factory;
        delete game;
    }
};

#endif //CPP_GAMECONTROLLER_H
