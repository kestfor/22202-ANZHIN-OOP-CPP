#ifndef BITARRAY_H
#define BITARRAY_H
#include <cmath>
#include <iostream>

template<typename blockType>
class BitArray {
private:

    //data size
    static const int bytesPerBlock = sizeof(blockType);
    static const int bitsPerBlock =  bytesPerBlock * 8;

    //main array
    blockType *array;

    // size of array in bytes
    int capacityInBytes;

    // size of array in bites
    int capacityInBites;

    //used amount of bits
    int currSizeInBites;

    //return index of last unused byte
    [[nodiscard]] int lastUnusedByteInd() const;
public:

    BitArray();

    ~BitArray();

    explicit BitArray(int numBits, blockType value = 0);

    BitArray(const BitArray &b);

    void swap(BitArray &other);

    BitArray& operator=(const BitArray& other);

    void resize(int numBits, bool value = false);

    void clear();

    void pushBack(bool bit);

    BitArray& operator&=(const BitArray& b);

    BitArray& operator|=(const BitArray& b);

    BitArray& operator^=(const BitArray& b);

    BitArray& operator<<=(int n);

    BitArray& operator>>=(int n);

    BitArray operator<<(int n) const;

    BitArray operator>>(int n) const;

    BitArray& set(int n, bool val = true);

    BitArray<blockType>& set();

    BitArray& reset(int n);

    BitArray& reset();

    bool any() const;

    bool none() const;

    BitArray operator~() const;

    int count() const;

    bool operator[](int i) const;

    int size() const;

    bool empty() const;

    std::string to_string() const;
};

#endif /* BITARRAY_H */
