#ifndef MIXER_H
#define MIXER_H
#include "Converter.h"
#include "../Exceptions.h"


class Mixer : public Converter {
protected:
    int startSec;
    int refInd;

    static void checkArgs(const int refInd, const int startSec) {
        if (refInd < 0) {
            throw ConverterException("refInd cannot be negative", ConverterException::INVALID_PARAM);
        }
        if (startSec < 0) {
            throw ConverterException("start second cannot be negative", ConverterException::INVALID_PARAM);
        }
    }

public:
    SampleFlow *convert(SampleFlow *previousFlow, const vector<SampleFlow*> &samples, const pair<int, int> &timeFrame) const override;

    explicit Mixer(const int refInd, const int startSec=0) {
        this->refInd = refInd;
        this->startSec = startSec;
        checkArgs(refInd, startSec);
    }

    explicit Mixer(const std::vector<int> &args) {
        if (args.size() < 1) {
            throw ConverterException("wrong amount of params in mix command", ConverterException::INVALID_AMOUNT_PARAMS);
        }
        this->refInd = args[0];
        if (args.size() > 1) {
            this->startSec = args[1];
        } else {
            this->startSec = 0;
        }
        checkArgs(refInd, startSec);
    }

};



#endif //MIXER_H
