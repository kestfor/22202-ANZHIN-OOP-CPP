#ifndef CPP_COMMANDFACTORY_H
#define CPP_COMMANDFACTORY_H

#include "Command.h"

//class CommandFactory {
//protected:
//    typedef std::map<std::string, Command*> FactoryMap;
//    FactoryMap factory;
//
//    void defaultInit() {
//        factory["tick"] = new TickCommand();
//        factory["t"] = new TickCommand();
//        factory["dump"] = new DumpCommand();
//        factory["exit"] = new ExitCommand();
//        factory["help"] = new HelpCommand();
//        factory["live"] = new LiveCommand();
//    }
//
//public:
//
//    ~CommandFactory() {
//        for (const auto &item : factory) {
//            delete item.second;
//        }
//    }
//
//    CommandFactory() {
//        defaultInit();
//    }
//
//    template<class C> void add(const std::string &name) {
//        if (factory.contains(name)) {
//            delete factory[name];
//        }
//        factory[name] = new C();
//    }
//
//    Command *get(const string &name) {
//        if (factory.contains(name)) {
//            return factory[name];
//        }
//        return nullptr;
//    }
//
//    bool contains(const string &name) {
//        return factory.contains(name);
//    }
//};

class abstractFooCreator {
public:
    abstractFooCreator() = default;
    virtual ~abstractFooCreator() = default;
    virtual Command *create() const = 0;
};

template<class C>
class CommandCreator : public abstractFooCreator {
public:
    virtual Command *create() const {
        return new C();
    }
};

class CommandFactory {
protected:
    typedef std::map<std::string, abstractFooCreator*> FactoryMap;
    FactoryMap _factory;

public:

    virtual ~CommandFactory() {
        for (const auto& item: _factory) {
            delete item.second;
        }
    };

    template<class C>
    void add(const std::string &name) {
        auto it = _factory.find(name);
        if (it == _factory.end())
            _factory[name] = new CommandCreator<C>();
    }

    Command *create(const std::string &name) {
        auto it = _factory.find(name);
        if (it != _factory.end())
            return it->second->create();
        return nullptr;
    }

    bool contains(const std::string name) {
        return _factory.contains(name);
    }

};


#endif //CPP_COMMANDFACTORY_H
