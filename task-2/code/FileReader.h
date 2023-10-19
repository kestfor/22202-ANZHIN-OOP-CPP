#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <stdexcept>
#include <filesystem>
using namespace std;

#ifndef CPP_FILEREADER_H
#define CPP_FILEREADER_H


class FileReader {
private:
    string fileName;
    ifstream *file = nullptr;
    streampos namePos;
    streampos rulesPos;
    streampos coordPos;

    void reOpen() const {
        file->close();
        file->open(fileName);
    }

    static void rtrim(string &s) {
        s.erase(s.find_last_not_of(" \n\r\t")+1);
    }

    /**
     * checks file format
     * @return true if its in Life 1.06 format else false
     */
    bool verifyFile() const {
        string line;
        getline(*this->file, line);
        rtrim(line);
        if (line != "#Life 1.06") {
            return false;
        }
        return true;
    }

    /**
     * sets pointers of name, rules, coords from file
     */
    void setSeeks();

public:

    explicit FileReader(const string &fileName) {
        if (!std::filesystem::exists(fileName)) {
            throw std::invalid_argument("file does not exist");
        }
        this->fileName = fileName;
        this->file = new ifstream(fileName, ios::binary);
        if (!verifyFile()) {
            throw std::runtime_error(fileName + " file not in Life 1.06 format");
        }
        setSeeks();
    }

    explicit FileReader() {
        this->file = new ifstream();
    }

    bool isOpen() const {
        return this->file->is_open();
    }

    void open(const string &fileName) {
        if (!this->file->is_open()) {
            this->fileName = fileName;
            this->file->open(fileName, ios::binary);
        }
        if (!isOpen()) {
            throw std::runtime_error("file cannot be opened");
        }
        if (!verifyFile()) {
            throw std::runtime_error("file not in Life 1.06 format");
        }
        setSeeks();
    }

    void close() {
        if (isOpen()) {
            file->close();
        }
    }

    string getUniverseName() const;

    pair<list<int>, list<int>> getBirthSurviveRules() const;

    list<pair<int, int>> readCoords() const;

    ~FileReader() {
        if (isOpen()) {
            file->close();
        }
        delete file;
    }
};


#endif //CPP_FILEREADER_H
