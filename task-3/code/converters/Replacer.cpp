#include "Replacer.h"

SampleFlow* Replacer::convert(SampleFlow* previousFlow, const vector<SampleFlow *>&samples,
                              const pair<int, int>&timeFrame) const {
    const int sampleInd = refInd - 1;
    const int startSecond = std::max(startSec, timeFrame.first);
    int endSecond =  this->endSec == -1? timeFrame.second : this->endSec;
    if (previousFlow == nullptr) {
        previousFlow = samples[0];
    }
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
