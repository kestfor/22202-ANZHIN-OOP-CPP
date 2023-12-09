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
            if (file == nullptr) {
                file = new std::ofstream;
            }
            file->open(fileName, std::ios::binary);
        } else {
            file->close();
            this->fileName = "";
            open(fileName);
        }
    }

    WAVWriter(const WAVWriter &w)  : WAVBase(w) {
        this->fileName = w.fileName;
        this->file = new std::ofstream(fileName, std::ios::binary);
        this->data = w.data;
        this->fmt = w.fmt;
        this->header = w.header;
        this->dataPlace = w.dataPlace;
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

    /**
     * \brief writes RIFF header to the file
     */
    void writeHeader();

    /**
     * \brief wtites FMT chunk with ingo to the file
     */
    void writeFmt();

    /**
     * \brief writes size of data that will be written to the file
     * \param dataSize
     */
    void writeDataInfo(int dataSize);

    /**
     * \brief writes data from sample flow
     * \param sampleFlow
     */
    void writeSampleFlow(const SampleFlow *sampleFlow);

    /**
     * \brief set seeker to the start of sample flow data
     */
    void resetDataSeeker() const;

};

#endif //WAVWRITER_H
