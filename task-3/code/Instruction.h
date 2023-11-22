#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "converters/ConverterFactory.h"
#include "Exceptions.h"
using std::string;

class Instruction {
protected:
    Converter *converter = nullptr;
    string converterName;
    vector<int> argsInt;
    vector<string> argsString;
    ConverterFactory *factory;

    static vector<string> split(const string &line);

    static vector<int> convertArgs(const vector<string> &args);


public:
    Instruction(const string &line, ConverterFactory *factory) {
        auto splited = split(line);
        if (splited.empty()) {
            throw InstructionException("empty line cannot be interpreted as command", InstructionException::EMPTY_COMMAND);
        }
        converterName = splited[0];
        this->factory = factory;
        if (factory->contains(converterName)) {
            const auto params = vector<string>(++splited.begin(), splited.end());
            argsInt = convertArgs(params);
            argsString = params;
            converter = factory->create(converterName, argsString);
        } else {
            throw InstructionException("no avaible converters with name '" + converterName + "'", InstructionException::INVALID_COMMAND_NAME);
        }
    }

    Converter *getConverter() const {
        return converter;
    }

    Instruction(const Instruction &inst) {
        this->converterName = inst.converterName;
        this->argsInt = inst.argsInt;
        this->argsString = inst.argsString;
        this->converter = inst.factory->create(converterName, this->argsInt);
        this->factory = inst.factory;
    }

    ~Instruction() {
        delete converter;
    }
};



#endif //INSTRUCTION_H
