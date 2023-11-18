#ifndef CPP_LIVECOMMAND_H
#define CPP_LIVECOMMAND_H
#include "Command.h"
#include <windows.h>

class LiveCommand : public Command {
public:
    void execute(Life *life, std::vector<std::string> &arguments) override {
        int n = 50;
        if (!arguments.empty()) {
            try {
                n = std::stoi(arguments[0]);
            } catch (const std::invalid_argument &err) {
                std::cout << "amount should be a number, type 'help' to learn more\n";
                return;
            }
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
