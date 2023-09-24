#include "BitArray.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

template<typename blockType>
BitArray<blockType>::~BitArray() {
    if (capacityInBytes != 0) {
        delete array;
    }
}

template<typename blockType>
BitArray<blockType>::BitArray() {
    currSizeInBites = 0;
    capacityInBites = bitsPerBlock;
    capacityInBytes = sizeof(blockType);
    array = (blockType *) malloc(capacityInBytes);
}

template<typename blockType>
BitArray<blockType>::BitArray(int numBits, blockType value) {
    currSizeInBites = numBits;
    capacityInBytes = std::max(size_t(ceil((double) numBits / 8)), sizeof(blockType));
    capacityInBites = capacityInBytes * 8;
    array = (blockType *) malloc(capacityInBytes);
    array[0] = value;
}

template<typename blockType>
BitArray<blockType>::BitArray(const BitArray &b) {
    if (*this == b) {
        return;
    }
    currSizeInBites = b.currSizeInBites;
    capacityInBites = b.capacityInBites;
    capacityInBytes = b.capacityInBytes;
    array = (blockType *) malloc(capacityInBytes);
    memcpy(array, b.array, capacityInBytes);
}

template<typename blockType>
int BitArray<blockType>::lastUnusedByteInd() const {
   return ceil((double) currSizeInBites / bitsPerBlock);
}

template<typename blockType>
void BitArray<blockType>::swap(BitArray &other) {
    if (other.currSizeInBites != this->currSizeInBites) {
        throw std::runtime_error("arrays size mismatch");
    } else {
        int lastByte = lastUnusedByteInd();
        for (int i = 0; i < lastByte; i++) {
            char tmp;
            tmp = *(this->array + i);
            *(this->array + i) = *(other.array + i);
            *(other.array + i) = tmp;
        }
    }
}

template<typename blockType>
bool BitArray<blockType>::operator[](int i) const {
    if (i < 0 || i >= currSizeInBites || currSizeInBites == 0) {
        throw std::out_of_range("invalid index");
    } else {
        int byteNum = i / bitsPerBlock;
        int bitNum = i % 8;
        return (*(this->array + byteNum)) & (1 << (7 - bitNum));
    }
}

template<typename blockType>
void BitArray<blockType>::resize(int numBits, bool value) {
    int newCapacity = ceil((double) numBits / 8);
    newCapacity = std::max(sizeof(blockType), size_t(newCapacity));
    if (newCapacity != capacityInBytes) {
        auto *tmp = (blockType *) realloc(this->array, newCapacity);
        if (tmp != nullptr) {
            this->array = tmp;
            for (int i = capacityInBites; i < numBits; i++) {
                this->set(i, value);
            }
            this->capacityInBites = numBits == 0 ? bitsPerBlock : numBits;
            this->capacityInBytes = newCapacity;
            this->currSizeInBites = capacityInBites;
        } else {
            throw std::runtime_error("unable to allocate memory");
        }
    } else {
        capacityInBites = numBits == 0 ? bitsPerBlock : numBits;
        capacityInBytes = newCapacity;
        currSizeInBites = capacityInBites;
    }
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::set(int n, bool val) {
    int byteNum = n / 8;
    int bitNum = n % 8;
    if (val) {
        *(this->array + byteNum)  |= (1 << (7 - bitNum));
    } else {
        *(this->array + byteNum) &= ~(1 << (7 - bitNum));
    }
    return *this;
}


template<typename blockType>
void BitArray<blockType>::pushBack(bool bit) {
    if (capacityInBites == currSizeInBites) {
        int old_size = currSizeInBites;
        resize(capacityInBites * 2);
        this->currSizeInBites = old_size;
    }
    this->set(currSizeInBites, bit);
    currSizeInBites++;
}


template<typename blockType>
int BitArray<blockType>::size() const {
    return this->currSizeInBites;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator=(const BitArray &other) {
    if (this == &other) {
        return *this;
    }
    this->clear();
    for (int i = 0; i < other.currSizeInBites; i++) {
        this->pushBack(other[i]);
    }
    return *this;
}

template<typename blockType>
void BitArray<blockType>::clear() {
    this->currSizeInBites = 0;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::set() {
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte; i++) {
        *(array + i) |= 255;
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator&=(const BitArray &b) {
    if (b.size() != this->size()) {
        throw std::runtime_error("arrays size mismatch");
    } else {
        int lastByte = lastUnusedByteInd();
        for (int i = 0; i < lastByte; i++) {
            *(array + i) &= *(b.array + i);
        }
    }
    return *this;
}

template<typename blockType>
BitArray<blockType>& BitArray<blockType>::reset(int n) {
    set(n, false);
}

template<typename blockType>
BitArray<blockType>& BitArray<blockType>::reset() {
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte; i++) {
        *(array + i) &= 0;
    }
    return *this;
}

template<typename blockType>
bool BitArray<blockType>::any() const {
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte - 1; i++) {
        if ((*array + i) != 0) {
            return true;
        }
    }
    if (lastByte > 0) {
        for (int i = (lastByte - 1) * 8; i < currSizeInBites; i++) {
            if ((*this)[i] != false) {
                return true;
            }
        }
    }
    return false;
}

template<typename blockType>
bool BitArray<blockType>::none() const {
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte - 1; i++) {
        if (*(array + i) != 0) {
            return false;
        }
    }
    if (lastByte > 0) {
        for (int i = (lastByte - 1) * 8; i < currSizeInBites; i++) {
            if ((*this)[i] != false) {
                return false;
            }
        }
    }
    return true;
}

template<typename blockType>
int BitArray<blockType>::count() const {
    int res = 0;
    for (int i = 0; i < currSizeInBites; i++) {
        if ((*this)[i]) {
            res++;
        }
    }
    return res;
}

template<typename blockType>
bool BitArray<blockType>::empty() const {
    return size() == 0;
}

template<typename blockType>
std::string BitArray<blockType>::to_string() const {
    std::string res;
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte; i++) {
        char alpha = (*(array + i));
        res.push_back(alpha);
    }
    return res;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator|=(const BitArray &b) {
    if (b.size() != this->size()) {
        throw std::runtime_error("arrays size mismatch");
    } else {
        int lastByte = lastUnusedByteInd();
        for (int i = 0; i < lastByte; i++) {
            *(array + i) |= *(b.array + i);
        }
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator^=(const BitArray &b) {
    if (b.size() != this->size()) {
        throw std::runtime_error("arrays size mismatch");
    } else {
        int lastByte = lastUnusedByteInd();
        for (int i = 0; i < lastByte; i++) {
            *(array + i) ^= *(b.array + i);
        }
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> BitArray<blockType>::operator~() const {
    auto res = BitArray<blockType>(*this);
    for (int i = 0; i < currSizeInBites; i++) {
        res.set(i, !(*this)[i]);
    }
    return res;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator<<=(int n) {
    if (n == 0) {
        return *this;
    }
    for (int i = 0; i < currSizeInBites; i++) {
        set(i, (i + n >= currSizeInBites ? 0 : (*this)[i + n]));
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator>>=(int n) {
    if (n == 0) {
        return *this;
    }
    for (int i = currSizeInBites - 1; i >= 0; i--) {
        set(i, (i - n < 0 ? 0 : (*this)[i - n]));
    }
    return *this;
}