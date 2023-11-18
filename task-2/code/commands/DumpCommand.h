#ifndef CPP_DUMPCOMMAND_H
#define CPP_DUMPCOMMAND_H
#include "Command.h"
#include "fstream"

class DumpCommand : public Command {
public:
    void execute(Life *life, std::vector<std::string> &arguments) override {
        if (arguments.empty()) {
            std::cout << "you should type file name after this command\n";
            return;
        }
        std::ofstream file(arguments[0]);
        file << "#Life 1.06\n";
        file << "#N " + life->getUniverseName() + '\n';
        file << "#R " + life->getBirthSurviveRules() + '\n';
        auto coords = life->getLiveCoords();
        for (const auto &item : coords) {
            file << item.first << ' ' << item.second << std::endl;
        }
        file.close();
        std::cout << "universe was successfully saved\n";
    }
};

#endif //CPP_DUMPCOMMAND_H
