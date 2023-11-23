#ifndef WAVPARSER_H
#define WAVPARSER_H
#include "WAVBase.h"
#include <vector>
#include <map>
#include <fstream>
#include <fstream>
#include <cstring>
#include <filesystem>
#include "Exceptions.h"
#include "SampleFlow.h"

using std::vector;
using std::map;
typedef char byte;


class WAVReader : public WAVBase  {
protected:

    string fileName;
    std::ifstream *file = nullptr;
    bool eof = false;
    constexpr static int buffSize = 16384;
    char buffer[buffSize];

public:

    explicit WAVReader(const string &fileName) {
        if (std::filesystem::exists(fileName)) {
            file = new std::ifstream(fileName, std::ios::binary);
            eof = false;
            file->rdbuf()->pubsetbuf(buffer, buffSize);
        } else {
            throw WAVException("file " + fileName + " doesn't exist", WAVException::INVALID_FILE_NAME);
        }
    }

    explicit WAVReader() = default;

    void open(const string &fileName) {
        if (!std::filesystem::exists(fileName)) {
            throw WAVException("file " + fileName + " doesn't exist", WAVException::INVALID_FILE_NAME);
        }
        if (this->fileName.empty()) {
            this->fileName = fileName;
            file->open(fileName, std::ios::binary);
            file->rdbuf()->pubsetbuf(buffer, buffSize);
            eof = false;
        } else {
            file->close();
            this->fileName = "";
            open(fileName);
        }
    }

    void close() const {
        if (file != nullptr) {
            file->close();
        }
    }

    ~WAVReader() override {
        close();
        delete file;
    }

    /**
     * \brief read Header of WAV file
     */
    void readHeader();

    /**
     * \brief read fmt chunk, data chunk, saves sample flow start position
     */
    void readChunkInfos();

    /**
     * \brief read header, fmt, data size
     */
    void readAllInfo();

    /**
     * \brief set file position to start of sample flow
     */
    void resetDataSeeker() const;

    /**
     * \brief read data in sample flow format
     * \param seconds duration of sample flow to read
     * \return
     */
    SampleFlow *readNext(int seconds = 10);

    bool hasNext() const {
        return !eof;
    }
};



#endif //WAVPARSER_H
