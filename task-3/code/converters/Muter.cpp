#include "Muter.h"

SampleFlow* Muter::convert(SampleFlow* previousFlow, const vector<SampleFlow *>&samples,
                           const pair<int, int>&timeFrame) const {
    if (previousFlow == nullptr) {
        previousFlow = samples[0];
    }

    auto* res = new SampleFlow(reinterpret_cast<int16_t *>(previousFlow->buffer()),
                               previousFlow->size() * sizeof(int16_t), previousFlow->getByteRate());
    const int startSecond = std::max(this->startSec, timeFrame.first);
    const int endSecond = std::min(this->endSec, timeFrame.first + previousFlow->getSeconds());
    if (endSecond - startSecond > 0) {
        auto [left, right] = getIndexRange({startSecond, endSecond}, timeFrame, previousFlow->getByteRate());
        right = std::min(right, previousFlow->size());
        for (int i = left; i < right; i++) {
            (*res)[i] = 0;
        }
    }
    return res;
}

vector<int> Muter::convertArgs(const vector<string>&args) {
    vector<int> res = {};
    if (args.size() != 2) {
        return res;
    }
    for (int i = 0; i < 2; i++) {
        try {
            res.push_back(std::stoi(args[i]));
        } catch (std::exception &error) {
            throw ConverterException("invalid start or end second", ConverterException::INVALID_PARAM);
        }
    }
    return res;
}
