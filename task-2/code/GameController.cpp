#include "GameController.h"

GameController::GameController(LifeSettings &settings) {
    factory = new CommandFactory();
    game = new Life(settings);
}

void GameController::waitForCommand() {
    string line;
    getline(std::cin, line);
    vector<string> cmdArguments = CommandArgumentService::parseCommand(line);
    if (cmdArguments.empty()) {
        return;
    }
    string name = cmdArguments[0];
    cmdArguments = vector<string>(cmdArguments.begin() + 1, cmdArguments.end());
    if (factory->contains(name)) {
        factory->get(name)->execute(game, cmdArguments);
    } else {
        std::cout << "wrong command, type 'help' to learn more\n";
    }
    waitForCommand();
}

void GameController::runGame() {
    game->showInfo();
    game->showField();
    waitForCommand();
}

void GameController::runGame(const string &amountTicks, const string &file) {
    auto tickArgs = vector<string>{amountTicks};
    auto dumpArgs = vector<string>{file};
    auto exitArgs = vector<string>();
    factory->get("tick")->execute(game, tickArgs);
    factory->get("dump")->execute(game, dumpArgs);
    factory->get("exit")->execute(game, exitArgs);
}
