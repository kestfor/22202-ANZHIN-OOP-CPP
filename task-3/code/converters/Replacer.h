#ifndef REPLACER_H
#define REPLACER_H
#include "Converter.h"
#include "../Exceptions.h"


class Replacer : public Converter {
protected:
    int startSec;
    int endSec;
    int refInd;

    static void checkArgs(const int refInd, const int startSec, const int endSec) {
        if (startSec > endSec && endSec != -1) {
            throw ConverterException("start second cannot be lower than end second", ConverterException::INVALID_PARAM);
        }
        if (startSec < 0 || endSec < -1) {
            throw ConverterException("time must be positive value", ConverterException::INVALID_PARAM);
        }
        if (refInd < 0) {
            throw ConverterException("reference index cannot be negative", ConverterException::INVALID_PARAM);
        }
    }

public:
    SampleFlow* convert(SampleFlow* previousFlow, const vector<SampleFlow*>& samples, const pair<int, int>& timeFrame) const override;

    explicit Replacer(const int refInd, const int startSec=0, const int endSec=-1) {
        checkArgs(refInd, startSec, endSec);
        this->refInd = refInd;
        this->startSec = startSec;
        this->endSec = endSec;
    }

    explicit Replacer(const std::vector<int> &args) {
        if (args.empty()) {
            throw ConverterException("wrong amount of params in replace command", ConverterException::INVALID_AMOUNT_PARAMS);
        }
        this->refInd = args[0];
        if (args.size() > 1) {
            this->startSec = args[1];
        } else {
            this->startSec = 0;
        }
        if (args.size() > 2) {
            this->endSec = args[2];
        } else {
            this->endSec = -1;
        }
        checkArgs(refInd, startSec, endSec);
    }
};



#endif //REPLACER_H
