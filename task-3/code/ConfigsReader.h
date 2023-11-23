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
    int currLine;
    ConverterFactory *factory = nullptr;



public:

    explicit ConfigsReader(const string &fileName) {
        if (!std::filesystem::exists(fileName)) {
            throw ConfigException("invalid file name '" + fileName + "'", ConfigException::INVALID_FILE_NAME);
        }
        this->file = new ifstream;
        currLine = 0;
        this->factory = new ConverterFactory();
        this->open(fileName);
    }

    explicit ConfigsReader() {
        this->file = new ifstream;
        currLine = 0;
        this->factory = new ConverterFactory();
    };

    void open(const string &fileName) {
        if (!std::filesystem::exists(fileName)) {
            throw ConfigException("invalid file name '" + fileName + "'", ConfigException::INVALID_FILE_NAME);
        }
        this->fileName = fileName;
        currLine = 0;
        if (file->is_open()) {
            file->close();
        }
        file->open(fileName);
    }

    /**
     * \brief read line from file
     * \return 
     */
    string readline();

    /**
     * \brief reads line from file and converts it into instruction
     * \return Instruction to execute
     */
    Instruction readInsruction();

    /**
     * \brief 
     * \return amount of read lines
     */
    int getLineNumber() const {
        return currLine;
    }

    /**
     * \brief add new available converter to use
     * \tparam Converter class of converter to add
     * \param name command name to access the converter
     */
    template<typename Converter>
    void addConverter(const string &name) const {
        this->factory->add<Converter>(name);
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

    /**
     * \brief 
     * \return vector of names of available converters
     */
    vector<string> getConverters() const {
        return factory->converterNames();
    }

    /**
     * \brief 
     * \return map of desriptions about every converter
     */
    const std::map<string, string> &getDescriptions() const {
        return factory->getDescriptions();
    }
};



#endif //CONFIGSREADER_H
