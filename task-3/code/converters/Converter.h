#ifndef CONVERTER_H
#define CONVERTER_H
#include <iostream>
#include <string>
#include <vector>
#include "../SampleFlow.h"
#include <algorithm>
using std::string;
using std::vector;
using std::pair;

class Converter {
protected:
    static pair<int, int> getIndexRange(const pair<int, int> &time, const pair<int, int> &frame, int byteRate);

public:

    Converter() = default;

    virtual ~Converter() = default;

    virtual SampleFlow *convert(SampleFlow *previousFlow, const vector<SampleFlow*> &samples, const pair<int, int> &timeFrame) const = 0;

};



#endif //CONVERTER_H
