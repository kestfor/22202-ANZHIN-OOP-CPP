#ifndef MUTER_H
#define MUTER_H
#include "Converter.h"
#include "../SampleFlow.h"
#include "../Exceptions.h"

class Muter : public Converter {
protected:
    int startSec;
    int endSec;

    static void checkArgs(const int startSec, const int endSec) {
        if (endSec < startSec) {
            throw ConverterException("start second cannot be lower than end second", ConverterException::INVALID_PARAM);
        }
        if (endSec < 0 || startSec < 0) {
            throw ConverterException("time must be positive value", ConverterException::INVALID_PARAM);
        }
    }

    static vector<int> convertArgs(const vector<string> &args);

public:
    static string description() {
        return "mute command has 2 required arguments: start second, end second\n"
                "example: mute <start second> <end second>";
    }

    SampleFlow *convert(SampleFlow *previousFlow, const vector<SampleFlow*> &samples, const pair<int, int> &timeFrame) const override;

    Muter(const int startSec, const int endSec) {
        checkArgs(startSec, endSec);
        this->startSec = startSec;
        this->endSec = endSec;
    }

    explicit Muter(const std::vector<int> &args) {
        if (args.size() != 2) {
            throw ConverterException("wrong amount of params in mute command", ConverterException::INVALID_AMOUNT_PARAMS);
        }
        this->startSec = args[0];
        this->endSec = args[1];
        checkArgs(startSec, endSec);
    }

    explicit Muter(const std::vector<string> &args) : Muter(convertArgs(args)) {}
};



#endif //MUTER_H
