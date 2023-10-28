#ifndef CPP_COMMAND_H
#define CPP_COMMAND_H
#include "../Life.h"
#include <string>


class Command {
protected:

public:

    virtual ~Command() = default;

    virtual void execute(Life *life, std::vector<std::string> &arguments) = 0;
};

#endif //CPP_COMMAND_H
