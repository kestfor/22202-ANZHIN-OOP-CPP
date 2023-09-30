#ifndef CPP_FILEWRITER_H
#define CPP_FILEWRITER_H
#include <string>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;

class FileWriter {
private:
    string fileName;
    ofstream *file;

    void checkError() {
        if (!isOpen()) {
            throw "the file is not open";
        }
    }

public:
    FileWriter(const string &fileName) {
        this->fileName = fileName;
        this->file = new ofstream();
    };

    ~FileWriter() {
        if (isOpen()) {
            file->close();
        }
        delete file;
    }

    void open() {
        this->file->open(fileName);
    }

    bool isOpen() {
        return this->file->is_open();
    }

    void close() {
        if (isOpen()) {
            file->close();
        }
        this->file->close();
    }

    void writeLine(const vector<string> &items) {
        checkError();
        string line;
        for (const auto &item : items) {
            line += item + '\t';
        }
        line[line.size() - 1] = '\n';
        writeLine(line);
    }

    void writeLine(const string &line) {
        checkError();
        *file << line << endl;
    }
};

#endif //CPP_FILEWRITER_H
