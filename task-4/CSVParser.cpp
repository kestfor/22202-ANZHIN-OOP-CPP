#include <sstream>
#include "CSVParser.h"
using std::enable_if;
using std::tuple;

template<typename... Args>
template<size_t I>
typename enable_if<(I == sizeof...(Args)), void>::type
CSVParser<Args...>::tupleAssigning(vector<string>&data, tuple<Args...>&t, int row) {
    return;
}

template<typename... Args>
template<size_t I>
typename enable_if<(I < sizeof...(Args)), void>::type
CSVParser<Args...>::tupleAssigning(vector<string>&data, tuple<Args...>&t, int row) {
    if (typeid(decltype(std::get<I>(t))).hash_code() == hashCodes[String]) {
        auto&value = reinterpret_cast<string &>(std::get<I>(t));
        value = processString(data[I]);
    }
    else {
        pair<int, int> place = {row, I + 1};
        convertValue<decltype(std::get<I>(t))>(data[I], std::get<I>(t), place);
    }
    tupleAssigning<I + 1>(data, t, row);
}


template<typename... Args>
std::tuple<Args...> CSVParser<Args...>::split(const string&row) {
    vector<string> splited;
    if (row.empty()) {
        return {};
    }
    size_t startInd = 0;
    const size_t endInd = row.size() - 1;
    while (startInd <= endInd) {
        while (startInd <= endInd && sep == row[startInd]) {
            startInd++;
        }
        for (size_t i = startInd; i <= endInd; i++) {
            if (sep == row[i]) {
                splited.push_back(row.substr(startInd, i - startInd));
                startInd = i + 1;
                break;
            }
            else if (i == endInd && sep != row[i]) {
                splited.push_back(row.substr(startInd, i - startInd + 1));
                startInd = i + 1;
            }
        }
    }
    const int amountArgsExpected = sizeof...(Args);
    if (amountArgsExpected != splited.size()) {
        const string errMsg = "error while parsing " + std::to_string(currRowNum) + " line\n" + "expected " +
                              std::to_string(amountArgsExpected) + " values, got " + std::to_string(splited.size());
        throw BasicException(errMsg, BasicException::INCOMPATIBLE_AMOUNT);
    }
    tupleAssigning(splited, *currData, currRowNum);
    return *currData;
}

template<typename... Args>
string CSVParser<Args...>::join(const vector<string>&data) const {
    string res;
    for (auto item: data) {
        int spaceInd = item.find(' ');
        while (spaceInd != -1) {
            item[spaceInd] = sep;
            spaceInd = item.find(' ');
        }
        res += item + ' ';
    }
    res.resize(res.size() - 1);
    return res;
}


template<typename... Args>
string CSVParser<Args...>::processString(const string&valueFrom) {
    string res = valueFrom;
    for (int i = 0; i < res.size(); i++) {
        if (res[i] == escapeChar && i + 1 != res.size()) {
            if (charsForReplace.contains(res[i + 1])) {
                const int indForReplace = i;
                for (int j = indForReplace; j < res.size(); j++) {
                    std::swap(res[j], res[j + 1]);
                }
                res[indForReplace] = charsForReplace[res[indForReplace]];
            }
        }
    }
    return res;
}

template<typename... Args>
template<typename T>
void CSVParser<Args...>::convertValue(const string&valueFrom, T&valueTo, pair<int, int>&place) {
    size_t code = typeid(T).hash_code();
    try {
        if (code == hashCodes[Double]) {
            valueTo = std::stod(valueFrom);
        }
        else if (code == hashCodes[Integer]) {
            valueTo = std::stoi(valueFrom);
        }
        else if (code == hashCodes[Float]) {
            valueTo = std::stof(valueFrom);
        }
        else if (code == hashCodes[Long]) {
            valueTo = std::stol(valueFrom);
        }
        else if (code == hashCodes[LongLong]) {
            valueTo = std::stoll(valueFrom);
        }
        else if (code == hashCodes[LongDouble]) {
            valueTo = std::stold(valueFrom);
        }
        else if (code == hashCodes[UnsignedLong]) {
            valueTo = std::stoul(valueFrom);
        }
        else if (code == hashCodes[UnsignedLongLong]) {
            valueTo = std::stoull(valueFrom);
        }
        else if ((code == hashCodes[Char] || code == hashCodes[UnsignedChar]) && valueFrom.size() == 1) {
            valueTo = valueFrom[0];
        }
        else if (code == hashCodes[String]) {
            return;
        }
        else {
            throw BasicException(
                "got unsupported type '" + string(typeid(T).name()) + "' on " + std::to_string(place.first) + " row " +
                std::to_string(place.second) + " column", BasicException::UNSUPPORTED_TYPE);
        }
    }
    catch (std::exception&err) {
        throw BasicException("got unexpected type '" + string(typeid(T).name()) + "' on " + std::to_string(place.first) + " row " +
                std::to_string(place.second) + " column", BasicException::UNEXPECTED_TYPE);
    }
}
