#ifndef WAVWRITER_H
#define WAVWRITER_H
#include "WAVBase.h"
#include "SampleFlow.h"

class WAVWriter : public WAVBase {
protected:
    string fileName;
    std::ofstream *file = nullptr;

public:

    explicit WAVWriter(const string &fileName) {
        file = new std::ofstream(fileName, std::ios::binary);
    };

    explicit WAVWriter() = default;

    void open(const string &fileName) {
        if (this->fileName.empty()) {
            this->fileName = fileName;
            file->open(fileName, std::ios::binary);
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

    ~WAVWriter() override {
        close();
        delete file;
    }

    void setHeader(const RIFFHeader &header) {
        this->header = header;
    }

    void setFmt(const FmtChunk &fmt) {
        this->fmt = fmt;
    }

    void writeHeader();

    void writeFmt();

    void writeDataInfo(int dataSize);

    void writeSampleFlow(const SampleFlow *sampleFlow);

    void resetDataSeeker() const;

};

#endif //WAVWRITER_H
