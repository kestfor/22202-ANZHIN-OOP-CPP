#ifndef CPP_EXITCOMMAND_H
#define CPP_EXITCOMMAND_H
#include "Command.h"

class ExitCommand : public Command {
public:
    void execute(Life *life, std::vector<std::string> &arguments) override {
        std::exit(EXIT_SUCCESS);
    }
};

#endif //CPP_EXITCOMMAND_H
