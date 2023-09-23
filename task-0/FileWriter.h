#ifndef CPP_FILEWRITER_H
#define CPP_FILEWRITER_H
#include <string>
#include <fstream>
using namespace std;

class FileWriter {
private:
    string fileName;
    ofstream *file;
public:
    FileWriter(const string &fileName) {
        this->fileName = fileName;
        this->file = new ofstream();
    };

    ~FileWriter() {
        delete file;
    }

    void open() {
        this->file->open(fileName);
    }

    bool isOpen() {
        return this->file->is_open();
    }

    void close() {
        this->file->close();
    }

    void writeLine(const string &line) {
        *file << line << endl;
    }
};

#endif //CPP_FILEWRITER_H
