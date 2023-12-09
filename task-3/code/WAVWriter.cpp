#include "WAVWriter.h"

void WAVWriter::writeHeader() {
    file->write(reinterpret_cast<char *> (&header), sizeof(header));
}

void WAVWriter::writeFmt() {
    ChunkInfo chunk;
    memcpy(chunk.chunkId, fmtId, sizeof(fmtId));
    chunk.chunkSize = sizeof(fmt);
    file->write(reinterpret_cast<char *> (&chunk), sizeof(chunk));
    file->write(reinterpret_cast<char *> (&fmt), sizeof(fmt));
}

void WAVWriter::writeDataInfo(const int dataSize) {
    ChunkInfo chunk;
    memcpy(chunk.chunkId, dataId, sizeof(fmtId));
    chunk.chunkSize = dataSize;
    file->write(reinterpret_cast<char *> (&chunk), sizeof(chunk));
    dataPlace = file->tellp();
}


void WAVWriter::resetDataSeeker() const {
    file->seekp(dataPlace);
}

void WAVWriter::writeSampleFlow(const SampleFlow *sampleFlow) {
    file->write(sampleFlow->buffer(), sampleFlow->buffSize() * sizeof(int16_t));
}

