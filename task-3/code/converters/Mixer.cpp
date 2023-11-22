#include "Mixer.h"

SampleFlow* Mixer::convert(SampleFlow *previousFlow,
                           const vector<SampleFlow *> &samples,
                           const pair<int, int> &timeFrame) const {
    if (previousFlow == nullptr) {
        previousFlow = samples[0];
    }
    const int sampleInd = this->refInd - 1;
    if (sampleInd >= samples.size()) {
        throw ConverterException("invalid reference in mix converter", ConverterException::INVALID_PARAM);
    }
    const int startSecond = std::max(this->startSec, timeFrame.first);
    const int endSecond = std::min(std::min(previousFlow->getSeconds(), samples[sampleInd]->getSeconds()) + startSecond, timeFrame.second);
    const int timePeriod = endSecond - startSecond;
    const auto firstSampleFlow = previousFlow;
    const auto secondSampleFlow = samples[sampleInd];
    const auto res = new SampleFlow(reinterpret_cast<int16_t *> (firstSampleFlow->buffer()),
                                    firstSampleFlow->getByteSize(),
                                    firstSampleFlow->getByteRate());
    if (timePeriod > 0) {
        auto [left, right] = getIndexRange({startSecond, endSecond}, timeFrame, res->getByteRate());
        right = std::min(right, firstSampleFlow->size());
        right = std::min(right, secondSampleFlow->size());
        for (int i = left; i < right; i++) {
            (*res)[i] = (static_cast<int> ((*firstSampleFlow)[i]) + static_cast<int> ((*secondSampleFlow)[i])) / 2;
        }
    }
    return res;
}
