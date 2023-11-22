#ifndef CONFIGSREADER_H
#define CONFIGSREADER_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Instruction.h"
#include "Exceptions.h"
#include <filesystem>
using std::string;
using std::ifstream;
using std::vector;


class ConfigsReader {
protected:
    string fileName;
    ifstream *file = nullptr;
    ConverterFactory *factory = nullptr;



public:

    explicit ConfigsReader(const string &fileName) {
        if (!std::filesystem::exists(fileName)) {
            throw ConfigException("invalid file name '" + fileName + "'", ConfigException::INVALID_FILE_NAME);
        }
        this->open(fileName);
        this->factory = new ConverterFactory();
    }

    explicit ConfigsReader() {
        this->file = nullptr;
        this->factory = new ConverterFactory();
    };

    void open(const string &fileName) {
        if (file == nullptr) {
            if (!std::filesystem::exists(fileName)) {
                throw ConfigException("invalid file name '" + fileName + "'", ConfigException::INVALID_FILE_NAME);
            }
            this->fileName = fileName;
            this->file = new ifstream(fileName);
        } else {
            file->close();
            delete file;
            open(fileName);
        }
    }

    string readline() const;

    Instruction readInsruction() const;

    template<typename T>
    void addConverter(const string &name) const {
        this->factory->add<T>(name);
    }


    void close() const {
        if (file != nullptr) {
            file->close();
        }
    }

    virtual ~ConfigsReader() {
        delete this->file;
        delete this->factory;
    }

    bool hasNext() const {
        return !file->eof();
    }

    ConverterFactory *getFactory() const {
        return factory;
    }

    vector<string> getConverters() const {
        return factory->converterNames();
    }
};



#endif //CONFIGSREADER_H
