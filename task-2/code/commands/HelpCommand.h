#ifndef CPP_HELPCOMMAND_H
#define CPP_HELPCOMMAND_H
#include "Command.h"

class HelpCommand : public Command {
public:
    void execute(Life *life, std::vector<std::string> &arguments) override {
        string line = "after start there are 5 commands that you can use:\n"
                      "1. dump <filename> - save current universe in file with name filename\n"
                      "2. tick <n=1> or in short t <n=1> for example: 'tick 2' command will show you your universe after 2 generations\n"
                      "3. exit - close the game, all progress will be lost\n"
                      "4. live <n=50> - run simulation in real time for n iterations\n"
                      "5. help - get info about commands\n";
        system("cls");
        std::cout << line;
    }
};


#endif //CPP_HELPCOMMAND_H
