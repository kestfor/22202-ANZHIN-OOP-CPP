#include "WAVReader.h"

SampleFlow *WAVReader::readNext(const int seconds) {
    if (!file->is_open()) {
        throw WAVException("file isn't open", WAVException::FILE_ERROR);
    }
    const int dataSize = seconds * fmt.byteRate;
    char *data = new char[dataSize];
    int readAmount = file->readsome(data, dataSize);
    int totalRead = readAmount;
    while (totalRead < dataSize && readAmount != 0) {
        readAmount = file->readsome(data + totalRead, dataSize - totalRead);
        totalRead += readAmount;
    }
    if (readAmount == 0) {
        eof = true;
    }
    SampleFlow *sampleFlow = new SampleFlow(reinterpret_cast<const int16_t *> (data), totalRead, fmt.byteRate);
    delete data;
    return sampleFlow;
}

void WAVReader::readHeader() {
    if (file == nullptr) {
        throw WAVException("file isn't opened", WAVException::FILE_ERROR);
    }
    file->read(reinterpret_cast<char *> (&header), sizeof(header));
    if (!file || memcmp(header.chunkId, riffId, 4) || memcmp(header.format, format, 4)) {
        throw WAVException("file " + this->fileName + " isn't in RIFF or WAVE format", WAVException::INVALID_FILE_NAME);
    }
}

void WAVReader::readChunkInfos() {
    ChunkInfo chunk;
    bool fmtRead = false;
    bool dataRead = false;
    while (file->read(reinterpret_cast<char *> (&chunk), sizeof(chunk))) {
        if (memcmp(fmtId, chunk.chunkId, 4) == 0) {
            file->read(reinterpret_cast<char *> (&fmt), chunk.chunkSize);
            fmtRead = true;
        } else if (memcmp(dataId, chunk.chunkId, 4) == 0) {
            dataPlace = file->tellg();
            data = DataChunk(chunk.chunkSize / sizeof(uint16_t));
            dataRead = true;
        } else {
            file->seekg(chunk.chunkSize, std::ios_base::cur);
        }
        if (dataRead && fmtRead) {
            break;
        }
    }
    if (!dataRead || !fmtRead) {
        throw WAVException("file " + this->fileName + " doesn't contain data or format chunk", WAVException::BAD_FORMAT);
    }
}


void WAVReader::readAllInfo() {
    readHeader();
    readChunkInfos();
}

void WAVReader::resetDataSeeker() const {
    file->seekg(dataPlace);
}





