#ifndef CSVPARSER_H
#define CSVPARSER_H
#include "Exceptions.h"
#include <iterator>
#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <typeinfo>
using std::list;
using std::map;
using std::string;
using std::vector;
using std::pair;

template<typename... Args>
class CSVParser {
protected:
    std::ifstream&file;
    std::tuple<Args...>* currData;
    int currRowNum = 0;
    char sep;
    char escapeChar;

    enum controlCharacters {
        tab = 't',
        lineFeed = 'n',
        carriageReturn = 'r',
        backSpace = 'b',
    };

    //control characters codes
    map<char, char> charsForReplace = {
        {tab, 0x09},
        {lineFeed, 0x0A},
        {carriageReturn, 0x0D},
        {backSpace, 0x08}
    };

    //supported types for parsing
    enum hashNames {
        Double,
        Float,
        Integer,
        Long,
        LongDouble,
        LongLong,
        UnsignedLong,
        UnsignedLongLong,
        Char,
        UnsignedChar,
        String,
    };

    //hashes for supported types
    map<int, size_t> hashCodes = {
        {Double, typeid(double).hash_code()},
        {Float, typeid(double).hash_code()},
        {Integer, typeid(int).hash_code()},
        {Long, typeid(long).hash_code()},
        {LongDouble, typeid(long double).hash_code()},
        {LongLong, typeid(long long).hash_code()},
        {UnsignedLong, typeid(unsigned long).hash_code()},
        {UnsignedLongLong, typeid(unsigned long long).hash_code()},
        {Char, typeid(char).hash_code()},
        {UnsignedChar, typeid(unsigned char).hash_code()},
        {String, typeid(string).hash_code()}
    };

    //compile time end of recursion
    template<size_t I = 0>
    typename std::enable_if<(I < sizeof...(Args)), void>::type tupleAssigning(
        vector<string>&data, std::tuple<Args...>&t, int row);

    //compile time recursion for tuple forEach
    template<size_t I = 0>
    typename std::enable_if<(I == sizeof...(Args)), void>::type tupleAssigning(
        vector<string>&data, std::tuple<Args...>&t, int row);

    //string adaptation(replaces control characters)
    string processString(const string&valueFrom);

    //assigns value from string to item reference from tuple
    template<typename T>
    void convertValue(const string&valueFrom, T&valueTo, pair<int, int>&place);

public:
    class Iterator {
        using value_type = std::tuple<Args...>;
        using pointer = std::tuple<Args...> *;
        using reference = std::tuple<Args...> &;

    protected:
        pointer mainPointer;
        CSVParser* parser;

    public:
        explicit Iterator(pointer ptr, CSVParser* parser) {
            mainPointer = ptr;
            this->parser = parser;
        }

        reference operator*() const {
            return *mainPointer;
        }

        pointer operator->() const {
            return mainPointer;
        }

        Iterator& operator++() {
            this->mainPointer = parser->readNext();
            return *this;
        }

        Iterator operator++(int) {
            const Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator&it) const {
            return this->mainPointer == it.mainPointer;
        }

        bool operator!=(const Iterator&it) const {
            return this->mainPointer != it.mainPointer;
        }
    };

    explicit CSVParser(std::ifstream&file, int n = 0, const char sep = ',', const char escapeChar = '"') : file(file),
        sep(sep),
        escapeChar(escapeChar) {
        charsForReplace[escapeChar] = escapeChar;
        this->currRowNum = n + 1;
        while (*this && n > 0) {
            std::string tmp;
            std::getline(this->file, tmp);
            n--;
        }
        this->currData = new std::tuple<Args...>;
    }

    explicit operator bool() const {
        return !file.eof();
    }

    //splits line, assignes values to tuple
    std::tuple<Args...> split(const string&row);

    //read next line in tuple
    std::tuple<Args...>* readNext() {
        if (*this) {
            std::string line;
            std::getline(this->file, line);
            if (!line.empty()) {
                *currData = split(line);
                currRowNum++;
            }
            else {
                delete currData;
                currData = nullptr;
                return currData;
            }
        }
        else {
            delete currData;
            currData = nullptr;
        }
        return currData;
    }

    Iterator begin() {
        readNext();
        return Iterator(currData, this);
    }

    Iterator end() {
        return Iterator(nullptr, this);
    }

    ~CSVParser() {
        delete currData;
    }
};


#endif //CSVPARSER_H
