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
public:
    FileReader(const string &fileName) {
        this->fileName = fileName;
        this->file = new ifstream();
    };

    bool isOpen() {
        return this->file->is_open();
    }

    ~FileReader() {
        delete file;
    };

    void open() {
        this->file->open(fileName);
    }

    string next() {
        string line;
        getline(*file, line);
        return line;
    };

    bool hasNext() {
        return !file->eof();
    }

    void close() {
        file->close();
    }

    void reset() {
        file->seekg(0);
    }
};

#endif //CPP_FILEREADER_H
