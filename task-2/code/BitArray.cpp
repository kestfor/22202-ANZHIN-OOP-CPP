#include "BitArray.h"

template<typename blockType>
BitArray<blockType>::~BitArray() {
    if (capacityInBytes != 0) {
        delete[] array;
    }
}

template<typename blockType>
BitArray<blockType>::BitArray() {
    currSizeInBites = 0;
    capacityInBites = bitsPerBlock;
    capacityInBytes = sizeof(blockType);
    array = new blockType[capacityInBytes / bytesPerBlock];
}

template<typename blockType>
BitArray<blockType>::BitArray(int numBits, blockType value) {
    currSizeInBites = numBits;
    capacityInBytes = std::max(size_t(ceil((double) numBits / 8)), sizeof(blockType));
    capacityInBites = capacityInBytes * 8;
    array = new blockType[capacityInBytes / bytesPerBlock];
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
    array = new blockType[capacityInBytes / bytesPerBlock];
    memcpy(array, b.array, capacityInBytes);
}

template<typename blockType>
int BitArray<blockType>::lastUnusedByteInd() const {
   return ceil((double) currSizeInBites / 8);
}

template<typename blockType>
void BitArray<blockType>::reallocateArray(int numBits) {
    if (numBits < 0) {
        throw std::range_error("amount of bits must be positive value");
    }
    int newCapacity = ceil(ceil((double) numBits / 8) / bytesPerBlock) * bytesPerBlock;
    newCapacity = std::max(sizeof(blockType), size_t(newCapacity));
    if (newCapacity != capacityInBytes) {
        auto *tmp = (blockType *) realloc((void *) array, newCapacity);
        if (tmp != nullptr) {
            this->array = tmp;
        } else {
            throw std::runtime_error("unable to allocate memory");
        }
    }
    this->capacityInBites = numBits == 0 ? bitsPerBlock : newCapacity * 8;
    this->capacityInBytes = newCapacity;
    this->currSizeInBites = numBits;
}

template<typename blockType>
void BitArray<blockType>::swap(BitArray &other) {
    if (other.currSizeInBites != this->currSizeInBites) {
        throw std::runtime_error("arrays size mismatch");
    } else {
        int lastByte = lastUnusedByteInd();
        for (int i = 0; i < lastByte; i++) {
            MyByte tmp;
            tmp = *((MyByte *) this->array + i);
            *((MyByte *) this->array + i) = *((MyByte *) other.array + i);
            *((MyByte *) other.array + i) = tmp;
        }
    }
}

template<typename blockType>
void BitArray<blockType>::resize(int numBits, bool value) {
    int oldSize = this->currSizeInBites;
    reallocateArray(numBits);
    for (int i = oldSize; i < numBits; i++) {
        set(i, value);
    }
}

template<typename blockType>
void BitArray<blockType>::set(int n, bool val) const {
    if (n >= capacityInBites || n < 0) {
        throw std::out_of_range("invalid index");
    }
    int byteNum = n / 8;
    int bitNum = n % 8;
    if (val) {
        *((MyByte *) this->array + byteNum) |= (1 << (7 - bitNum));
    } else {
        *((MyByte *) this->array + byteNum) &= ~(1 << (7 - bitNum));
    }
}

template<typename blockType>
void BitArray<blockType>::pushBack(bool bit) {
    if (capacityInBites == currSizeInBites) {
        int old_size = currSizeInBites;
        reallocateArray(capacityInBites * 2);
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
    this->resize(other.capacityInBites);
    memcpy(this->array, other.array, other.capacityInBytes);
//    for (int i = 0; i < other.currSizeInBites; i++) {
//        this->pushBack(other.get(i));
//    }
    this->currSizeInBites = other.currSizeInBites;
    this->capacityInBytes = other.capacityInBytes;
    this->currSizeInBites = other.currSizeInBites;
    return *this;
}

template<typename blockType>
void BitArray<blockType>::clear() {
    this->currSizeInBites = 0;
}

template<typename blockType>
void BitArray<blockType>::set() {
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte; i++) {
        *((MyByte *) array + i) |= 255;
    }
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator&=(const BitArray &b) {
    if (b.size() != this->size()) {
        throw std::runtime_error("arrays size mismatch");
    } else {
        int lastByte = lastUnusedByteInd();
        for (int i = 0; i < lastByte; i++) {
            *((MyByte *) array + i) &= *((MyByte *) b.array + i);
        }
    }
}

template<typename blockType>
void BitArray<blockType>::reset(int n) {
    set(n, false);
}

template<typename blockType>
void BitArray<blockType>::reset() {
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte; i++) {
        *((MyByte *) array + i) &= 0;
    }
}

template<typename blockType>
bool BitArray<blockType>::any() const {
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte - 1; i++) {
        if (*((MyByte *) array + i) != 0) {
            return true;
        }
    }
    if (lastByte > 0) {
        for (int i = (lastByte - 1) * 8; i < currSizeInBites; i++) {
            if ((*this).get(i) != false) {
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
        if (*((MyByte *) array + i) != 0) {
            return false;
        }
    }
    if (lastByte > 0) {
        for (int i = (lastByte - 1) * 8; i < currSizeInBites; i++) {
            if ((*this).get(i) != false) {
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
        if ((*this).get(i)) {
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
std::string BitArray<blockType>::toString() const {
    std::string res;
    int lastByte = lastUnusedByteInd();
    for (int i = 0; i < lastByte; i++) {
        char alpha = (*((MyByte *) array + i));
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
            *((MyByte *) array + i) |= *((MyByte *) b.array + i);
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
            *((MyByte *) array + i) ^= *((MyByte *) b.array + i);
        }
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> BitArray<blockType>::operator~() const {
    auto res = BitArray<blockType>(*this);
    for (int i = 0; i < currSizeInBites; i++) {
        res.set(i, !(*this).get(i));
    }
    return res;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator<<=(int n) {
    if (n == 0) {
        return *this;
    }
    for (int i = 0; i < currSizeInBites; i++) {
        set(i, (i + n >= currSizeInBites ? 0 : (*this).get(i + n)));
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> &BitArray<blockType>::operator>>=(int n) {
    if (n == 0) {
        return *this;
    }
    for (int i = currSizeInBites - 1; i >= 0; i--) {
        set(i, (i - n < 0 ? 0 : (*this).get(i - n)));
    }
    return *this;
}

template<typename blockType>
BitArray<blockType> BitArray<blockType>::operator<<(int n) const {
    auto res = BitArray<blockType>(*this);
    res <<= n;
    return res;
}

template<typename blockType>
BitArray<blockType> BitArray<blockType>::operator>>(int n) const {
    auto res = BitArray<blockType>(*this);
    res >>= n;
    return res;
}

template<typename blockType>
BitArray<blockType>::Bit BitArray<blockType>::operator[](int i) const {
    if (i >= currSizeInBites || i < 0) {
        throw std::out_of_range("invalid index");
    }
    return Bit(this, i);
}

template<typename blockType>
BitArray<blockType>::Bit::Bit(const BitArray<blockType> *bitArray, int ind) {
    this->bitArray = bitArray;
    index = ind;
    value = bitArray->get(ind);
}

template<typename blockType>
BitArray<blockType>::Bit::Bit(const BitArray::Bit &b) {
    bitArray = b.bitArray;
    index = b.index;
    value = b.value;
}

template<typename blockType>
BitArray<blockType>::Bit &BitArray<blockType>::Bit::operator=(bool val) {
    bitArray->set(index, val);
    return *this;
}

template<typename blockType>
BitArray<blockType>::Bit &BitArray<blockType>::Bit::operator=(const BitArray::Bit &other) {
    if (other == this) {
        return  *this;
    }
    this->value = other.value;
    this->index = other.index;
    return *this;
}
