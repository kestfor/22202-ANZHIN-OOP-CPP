#ifndef WAVABSTRACT_H
#define WAVABSTRACT_H
#include <cstdint>
#include <fstream>
using std::string;

class WAVBase {
public:
    struct RIFFHeader{
        char chunkId[4];
        uint32_t chunkSize;
        char format[4];
    };

    struct ChunkInfo{
        char chunkId[4];
        uint32_t chunkSize;
    };

    struct DataChunk {
        int numberOfSamples;
    };

    struct FmtChunk{
        int16_t audioFormat;
        int16_t numChannels;
        int32_t sampleRate;
        int32_t byteRate;
        int16_t blockAlign;
        int16_t bitsPerSample;
    };

    explicit WAVBase() = default;

    virtual ~WAVBase() = default;

    virtual const DataChunk &getData() const {
        return data;
    }

    virtual const FmtChunk &getFmt() const {
        return fmt;
    }

    virtual const RIFFHeader &getHeader() const {
        return header;
    }



protected:
    constexpr static char riffId[4] = {'R','I','F','F'};
    constexpr static char format[4] = {'W','A','V','E'};
    constexpr static char fmtId[4] = {'f','m','t',' '};
    constexpr static char dataId[4] = {'d','a','t','a'};
    std::streampos dataPlace;
    RIFFHeader header;
    DataChunk data;
    FmtChunk fmt;

};

#endif //WAVABSTRACT_H
