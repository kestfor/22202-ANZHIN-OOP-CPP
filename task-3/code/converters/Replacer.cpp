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
