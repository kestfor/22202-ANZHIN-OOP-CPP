#include "GameController.h"

GameController::GameController(LifeSettings &settings) {
    factory = new CommandFactory();
    factory->add<DumpCommand>("dump");
    factory->add<TickCommand>("t");
    factory->add<TickCommand>("tick");
    factory->add<LiveCommand>("live");
    factory->add<ExitCommand>("exit");
    factory->add<HelpCommand>("help");
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
        //factory->create(name)->execute(game, cmdArguments);
        auto cmd = factory->create(name);
        cmd->execute(game, cmdArguments);
        delete cmd;
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
    vector<vector<string>> cmdArgs = {vector<string>{amountTicks}, vector<string>{file}, vector<string>()};
    vector<Command *> commands = {factory->create("tick"), factory->create("dump"), factory->create("exit")};
    for (int i = 0; i < 3; i++) {
        commands[i]->execute(game, cmdArgs[i]);
        delete commands[i];
    }
}
