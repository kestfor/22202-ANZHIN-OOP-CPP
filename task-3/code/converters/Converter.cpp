#include "Converter.h"

pair<int, int> Converter::getIndexRange(const pair<int, int>&time, const pair<int, int>&frame, const int byteRate) {
    int startSecond = time.first;
    int endSecond = time.second;
    const int timePeriod = frame.second - frame.first;
    int frameStartSecond = frame.first;
    int frameEndSecond = frame.second;
    int startInd = 0;
    int endInd = 0;
    if (startSecond <= frameStartSecond && frameStartSecond <= endSecond && startSecond <= frameEndSecond && frameEndSecond <= endSecond) {
        startInd = (frameStartSecond & timePeriod) * byteRate / sizeof(int16_t);
        endInd = ((frameEndSecond % timePeriod) == 0 ? timePeriod : frameEndSecond % timePeriod) * byteRate / sizeof(int16_t);
    }
    if (frameStartSecond <= startSecond && startSecond < frameEndSecond) {
        startInd = (startSecond % timePeriod) * byteRate / sizeof(int16_t);
        if (frameStartSecond < endSecond && endSecond <= frameEndSecond) {
            endInd = ((endSecond % timePeriod) == 0 ? timePeriod : endSecond % timePeriod) * byteRate / sizeof(int16_t);
        } else {
            endInd = ((frameEndSecond % timePeriod) == 0 ? timePeriod : frameEndSecond % timePeriod) * byteRate / sizeof(int16_t);
        }
    } else if (startSecond <= frameStartSecond && frameStartSecond < endSecond) {
        startInd = (frameStartSecond % timePeriod) * byteRate / sizeof(int16_t);
        endInd = ((endSecond % timePeriod) == 0 ? timePeriod : endSecond % timePeriod) * byteRate / sizeof(int16_t);
    }
    return {startInd, endInd};
}
