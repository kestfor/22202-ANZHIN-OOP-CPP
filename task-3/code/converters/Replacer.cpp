#include "Replacer.h"

SampleFlow* Replacer::convert(SampleFlow* previousFlow, const vector<SampleFlow *>&samples,
                              const pair<int, int>&timeFrame) const {
    if (previousFlow == nullptr) {
        previousFlow = samples[0];
    }
    const int sampleInd = refInd - 1;
    if (sampleInd >= samples.size()) {
        throw ConverterException("invalid reference in replace converter", ConverterException::INVALID_PARAM);
    }
    const int startSecond = std::max(startSec, timeFrame.first);
    int endSecond =  this->endSec == -1? timeFrame.second : this->endSec;
    endSecond = std::min(std::min(previousFlow->getSeconds(), samples[sampleInd]->getSeconds()) + startSecond, endSecond);
    endSecond = std::min(endSecond, timeFrame.second);
    const int timePeriod = endSecond - startSecond;
    const auto firstSampleFlow = previousFlow;
    const auto secondSampleFlow = samples[sampleInd];
    const auto res = new SampleFlow(reinterpret_cast<int16_t *>(firstSampleFlow->buffer()),
                                    firstSampleFlow->getByteSize(),
                                    firstSampleFlow->getByteRate());
    if (timePeriod > 0) {
        auto [left, right] = getIndexRange({startSecond, endSecond}, timeFrame, res->getByteRate());
        right = std::min(right, firstSampleFlow->size());
        right = std::min(right, secondSampleFlow->size());
        for (int i = left; i < right; i++) {
            (*res)[i] = (*secondSampleFlow)[i];
        }
    }
    return res;
}

vector<int> Replacer::convertArgs(const vector<string> &args) {
    vector<int> res = {};
    if (args.empty() || !args[0].starts_with("$")) {
        throw ConverterException("first argument in replace converter must be reference with '$' symbol", ConverterException::INVALID_PARAM);
    }
    const string refIndString = args[0].substr(1);
    try {
        res.push_back(std::stoi(refIndString));
    } catch (std::exception &error) {
        throw ConverterException("invalid reference index", ConverterException::INVALID_PARAM);
    }
    for (int i = 1; i < 3; i++) {
        if (args.size() > i) {
            try {
                res.push_back(std::stoi(args[i]));
            } catch (std::exception &error) {
                throw ConverterException("invalid start or end second in replace converter", ConverterException::INVALID_PARAM);
            }
        }
    }
    return res;
}

