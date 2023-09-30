#ifndef CPP_FILEREADER_H
#define CPP_FILEREADER_H
#include <string>
#include <fstream>
using std::string;
using std::ifstream;

class FileReader {
private:
    string fileName;
    ifstream *file;

    void checkError() {
        if (!isOpen()) {
            throw "the file is not open";
        }
    }

public:
    FileReader(const string &fileName) {
        this->fileName = fileName;
        this->file = new ifstream();
    };

    bool isOpen() {
        return this->file->is_open();
    }

    ~FileReader() {
        if (isOpen()) {
            file->close();
        }
        delete file;
    };

    void open() {
        this->file->open(fileName);
    }

    string next() {
        checkError();
        string line;
        getline(*file, line);
        return line;
    };

    bool hasNext() {
        checkError();
        return !file->eof();
    }

    void close() {
        checkError();
        file->close();
    }

    void reset() {
        checkError();
        file->seekg(0);
    }
};

#endif //CPP_FILEREADER_H
