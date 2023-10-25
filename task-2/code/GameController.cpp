#include "GameController.h"

GameController::GameController(int args, char *argv[]) {
    arguments = new CommandArgumentService(args, argv);
    if (arguments->contains("-f")) {
        game = new Life((*arguments)["-f"]);
    } else {
        game = new Life();
    }
    if (arguments->contains("-i") && arguments->contains("-o")) {
        Command cmd(this->game);
        vector<string> cmd1 = CommandArgumentService::parseCommand("tick " + arguments->getArgument("-i"));
        vector<string> cmd2 = CommandArgumentService::parseCommand("dump " + arguments->getArgument("-o"));
        vector<string> cmd3 = CommandArgumentService::parseCommand("exit");
        cmd.execute(cmd1);
        cmd.execute(cmd2);
        cmd.execute(cmd3);
    } else {
        game->showInfo();
        game->show();
    }

}

void GameController::waitForCommand() {
    string line;
    getline(std::cin, line);
    vector<string> cmdArguments = CommandArgumentService::parseCommand(line);
    Command cmd(this->game);
    cmd.execute(cmdArguments);
}
