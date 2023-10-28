#ifndef CPP_TICKCOMMAND_H
#define CPP_TICKCOMMAND_H
#include "Command.h"

class TickCommand : public Command {
public:

    void execute(Life *life, std::vector<std::string> &arguments) override {
        int n;
        if (arguments.empty()) {
            n = 1;
        } else {
            n = std::stoi(arguments[0]);
        }
        if (n >= 1000) {
            std::cout << "calculating...\n";
        }
        for (int i = 0; i < n; i++) {
            life->nextGeneration();
        }
        system("cls");
        std::cout << life->getUniverseName() << std::endl;
        std::cout << life->getBirthSurviveRules() << std::endl;
        std::cout << "current gen: " << life->getGenNumber() << std::endl;
        life->showField();
    }

};


#endif //CPP_TICKCOMMAND_H
