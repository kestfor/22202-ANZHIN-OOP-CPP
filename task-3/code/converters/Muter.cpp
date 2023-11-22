#include "Muter.h"

SampleFlow* Muter::convert(SampleFlow* previousFlow, const vector<SampleFlow *>&samples,
                           const pair<int, int>&timeFrame) const {
    if (previousFlow == nullptr) {
        previousFlow = samples[0];
    }

    auto* res = new SampleFlow(reinterpret_cast<int16_t *>(previousFlow->buffer()),
                               previousFlow->size() * sizeof(int16_t), previousFlow->getByteRate());
    int startSecond = std::max(this->startSec, timeFrame.first);
    int endSecond = std::min(this->endSec, timeFrame.first + previousFlow->getSeconds());
    auto [left, right] = getIndexRange({startSecond, endSecond}, timeFrame, previousFlow->getByteRate());
    right = std::min(right, previousFlow->size());
    for (int i = left; i < right; i++) {
        (*res)[i] = 0;
    }
    return res;
}
