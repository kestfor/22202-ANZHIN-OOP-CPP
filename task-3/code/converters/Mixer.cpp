#include "Mixer.h"

SampleFlow* Mixer::convert(SampleFlow *previousFlow,
                           const vector<SampleFlow *> &samples,
                           const pair<int, int> &timeFrame) const {
    if (previousFlow == nullptr) {
        previousFlow = samples[0];
    }
    const int sampleInd = this->refInd;
    const int startSecond = std::max(this->startSec, timeFrame.first);
    const int endSecond = std::min(previousFlow->getSeconds(), samples[sampleInd]->getSeconds()) + startSecond;
    const int timePeriod = endSecond - startSecond;
    const auto firstSampleFlow = previousFlow;
    const auto secondSampleFlow = samples[sampleInd];
    const auto res = new SampleFlow(reinterpret_cast<int16_t *> (firstSampleFlow->buffer()),
                                    firstSampleFlow->size() * sizeof(int16_t),
                                    firstSampleFlow->getByteRate());
    if (timePeriod > 0) {
        auto [left, right] = getIndexRange({startSecond, endSecond}, timeFrame, res->getByteRate());
        right = std::min(firstSampleFlow->size(), right);
        for (int i = left; i < right; i++) {
            (*res)[i] = (static_cast<int> ((*firstSampleFlow)[i]) + static_cast<int> ((*secondSampleFlow)[i])) / 2;
        }
    }
    return res;
}
