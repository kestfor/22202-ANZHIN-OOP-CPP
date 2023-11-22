#include "Instruction.h"

vector<string> Instruction::split(const string &line) {
    vector<string> result;
    if (line.empty()) {
        return result;
    }
    size_t startInd = 0;
    size_t endInd = line.size() - 1;
    while (startInd <= endInd) {
        while (startInd <= endInd && line[startInd] == ' ') {
            startInd++;
        }
        for (size_t i = startInd; i <= endInd; i++) {
            if (line[i] == ' ') {
                result.push_back(line.substr(startInd, i - startInd));
                startInd = i + 1;
                break;
            } else if (i == endInd && line[i] != ' ') {
                result.push_back(line.substr(startInd, i - startInd + 1));
                startInd = i + 1;
            }
        }
    }
    return result;
}

vector<int> Instruction::convertArgs(const vector<string>& args) {
    vector<int> res = {};
    for (auto item : args) {
        if (item.starts_with("$")) {
            item = item.substr(1);
        }
        try {
            res.push_back(std::stoi(item));
        } catch (std::exception &error) {
            throw InstructionException("invalid format of reference index", InstructionException::INVALID_PARAM);
        }
    }
    return res;
}

