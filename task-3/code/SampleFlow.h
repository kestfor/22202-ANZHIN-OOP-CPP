#ifndef SAMPLE_H
#define SAMPLE_H
#include <cmath>
#include <cstdint>
#include <cstring>
#include <stdexcept>

class SampleFlow {
protected:
    const int DEFAULT_BUFFERED_SECONDS = 10;
    int16_t *partOfData = nullptr;
    int bufferedSeconds = DEFAULT_BUFFERED_SECONDS;
    int arraySize;
    int byteSize;
    int byteRate;

public:
    /**
     * \brief create sample flow with given data
     * \param data sample flow
     * \param byteSize size of sample flow
     * \param byteRate byte rate of sample flow
     */
    SampleFlow(const int16_t *data, const int byteSize, const int byteRate) {
        this->bufferedSeconds = std::ceil(static_cast<float> (byteSize) / byteRate);
        this->byteRate = byteRate;
        this->arraySize = bufferedSeconds * byteRate / sizeof(int16_t);
        this->byteSize = byteSize;
        this->partOfData = new int16_t[arraySize];
        if (data != nullptr) {
            memcpy(this->partOfData, data, byteSize);
        }
    }

    /**
     * \brief create empty sample flow
     * \param seconds duration of sample flow
     * \param byteRate byte rate of sample flow
     */
    SampleFlow(const int seconds, const int byteRate) {
        this->arraySize = seconds * byteRate / sizeof(int16_t);
        this->byteSize = seconds * byteRate;
        this->byteRate = byteRate;
        this->partOfData = new int16_t[arraySize];
        this->bufferedSeconds = seconds;
        memset(this->partOfData, 0, arraySize * sizeof(int16_t));
    }


    /**
     * \brief initialize all field to zero
     */
    SampleFlow() {
        this->arraySize = 0;
        this->bufferedSeconds = 0;
        this->byteRate = 0;
        this->byteSize = 0;
        this->arraySize = 0;
        this->partOfData = nullptr;
    }

    int16_t& operator[](const int i) const {
        if (i >= size() || i < 0) {
            throw std::range_error("index out of range");
        }
        return partOfData[i];
    }

    /**
     * \brief
     * \return amount samples in flow
     */
    int size() const {
        return this->byteSize / sizeof(int16_t);
    }

    /**
     * \brief
     * \return size of sample flow in bytes
     */
    int getByteSize() const {
        return this->byteSize;
    }

    SampleFlow(const SampleFlow &s) {
        *this = s;
    }

    SampleFlow &operator=(const SampleFlow &s) {
        if (&s == this) {
            return *this;
        }
        if (this->partOfData != nullptr) {
            delete[] this->partOfData;
        }
        this->arraySize = s.arraySize;
        this->byteSize = s.byteRate;
        this->bufferedSeconds = s.bufferedSeconds;
        this->byteRate = s.byteRate;
        this->partOfData = new int16_t[arraySize];
        memcpy(this->partOfData, s.partOfData, byteSize);
        return *this;
    }

    ~SampleFlow() {
        delete[] partOfData;
    }

    /**
     * \brief
     * \return byte rate of sample
     */
    int getByteRate() const {
        return this->byteRate;
    }

    /**
     * \brief
     * \return raw data of sample flow
     */
    char *buffer() const {
        return reinterpret_cast<char *> (partOfData);
    }

    /**
     * \brief
     * \return amount of allocated samples for data
     */
    int buffSize() const {
        return arraySize;
    }

    int getSeconds() const {
        return bufferedSeconds;
    }


};


#endif //SAMPLE_H
