#ifndef CPP_COMMANDFACTORY_H
#define CPP_COMMANDFACTORY_H
#include "Command.h"
#include "../commands/DumpCommand.h"
#include "../commands/TickCommand.h"
#include "../commands/HelpCommand.h"
#include "../commands/LiveCommand.h"
#include "../commands/ExitCommand.h"

class CommandFactory {
protected:
    typedef std::map<std::string, Command*> FactoryMap;
    FactoryMap factory;

    void defaultInit() {
        factory["tick"] = new TickCommand();
        factory["t"] = new TickCommand();
        factory["dump"] = new DumpCommand();
        factory["exit"] = new ExitCommand();
        factory["help"] = new HelpCommand();
        factory["live"] = new LiveCommand();
    }

public:

    ~CommandFactory() {
        for (const auto &item : factory) {
            delete item.second;
        }
    }

    CommandFactory() {
        defaultInit();
    }

    template<class C> void add(const std::string &name) {
        if (factory.contains(name)) {
            delete factory[name];
        }
        factory[name] = new C();
    }

    Command *get(const string &name) {
        if (factory.contains(name)) {
            return factory[name];
        }
        return nullptr;
    }

    bool contains(const string &name) {
        return factory.contains(name);
    }
};


#endif //CPP_COMMANDFACTORY_H
