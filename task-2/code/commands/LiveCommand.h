#ifndef CPP_LIVECOMMAND_H
#define CPP_LIVECOMMAND_H
#include "Command.h"
#include <windows.h>

class LiveCommand : public Command {
public:
    void execute(Life *life, std::vector<std::string> &arguments) override {
        int n = 50;
        if (!arguments.empty()) {
            n = std::stoi(arguments[0]);
        }
        system("cls");
        std::cout << life->getUniverseName() << std::endl;
        std::cout << life->getBirthSurviveRules() << std::endl;
        COORD coord;
        for (int i = 0; i < n; i++) {
            coord.Y = 2;
            coord.X = 0;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            life->nextGeneration();
            std::cout << "current gen: " << life->getGenNumber() << std::endl;
            life->showField();
            Sleep(50);
            if (life->getAmountAlive() == 0) {
                break;
            }
        }
    }
};


#endif //CPP_LIVECOMMAND_H
