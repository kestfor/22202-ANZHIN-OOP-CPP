#ifndef BITARRAY_H
#define BITARRAY_H
#include <cmath>
#include <iostream>

template<typename blockType>
class BitArray {
private:

    typedef unsigned char byte;

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

    //returns index of last unused byte
    [[nodiscard]] int lastUnusedByteInd() const;

    //reallocates array memory, changes current size, capacity
    void reallocateArray(int numBits);
public:

    //creates empty array reserving memory with size of one 'blockType'
    BitArray();

    //clears allocated memory
    ~BitArray();

    //creates array with size of numbits, first size of 'blockType' bytes initialises as 'value'
    explicit BitArray(int numBits, blockType value = 0);

    //copy constructor
    BitArray(const BitArray &b);

    //swaps two arrays, throw runtime error if sizes are not equal
    void swap(BitArray &other);

    //copies other's array bits, resizes array if needed
    BitArray& operator=(const BitArray& other);

    //changes size of array to numbits, if new size bigger, then new bits initialises as 'value'
    void resize(int numBits, bool value = false);

    //changes size of array to 0
    void clear();

    //adds new bit to the end
    void pushBack(bool bit);

    //Bitwise AND, changes original array, throw runtime error if sizes are not equal
    BitArray& operator&=(const BitArray& b);

    //Bitwise OR, changes original array, throw runtime error if sizes are not equal
    BitArray& operator|=(const BitArray& b);

    //Bitwise XOR, changes original array, throw runtime error if sizes are not equal
    BitArray& operator^=(const BitArray& b);

    //Bitwise left shift, changes original array
    BitArray& operator<<=(int n);

    //Bitwise right shift, changes original array
    BitArray& operator>>=(int n);

    //Bitwise left shift, create new object
    BitArray operator<<(int n) const;

    //Bitwise right shift, create new object
    BitArray operator>>(int n) const;

    //sets bit at index n to the value = 'val', throw range error if index out of range
    BitArray& set(int n, bool val = true);

    //sets all bits to the 1
    BitArray<blockType>& set();

    //sets bit at index n to the value = 0, throw range error if index out of range
    BitArray& reset(int n);

    //sets all bits to the 0
    BitArray& reset();

    //returns true if there is any nonzero bit
    bool any() const;

    //returns true if all bits are zero
    bool none() const;

    //Bitwise NOT, creates new object
    BitArray operator~() const;

    //returns amount of nonzero bits
    int count() const;

    //returns value of bit at 'i' index, throw range error if index out of range
    bool operator[](int i) const;

    //returns amount of bits, used in array
    int size() const;

    //returns true if size is 0
    bool empty() const;

    //turn every byte to char, returns string of this chars
    std::string toString() const;
};


//Bitwise left shift, returns new object
template<typename blockType>
BitArray<blockType> BitArray<blockType>::operator<<(int n) const {
    auto res = BitArray<blockType>(*this);
    res <<= n;
    return res;
}

//Bitwise right shift, returns new object
template<typename blockType>
BitArray<blockType> BitArray<blockType>::operator>>(int n) const {
    auto res = BitArray<blockType>(*this);
    res >>= n;
    return res;
}


//returns true if arrays are equal
template<typename blockType>
bool operator==(const BitArray<blockType> & a, const BitArray<blockType> & b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

template<typename blockType>
bool operator!=(const BitArray<blockType> & a, const BitArray<blockType> & b) {
    return ! (a == b);
}

//Bitwise AND, returns new object
template<typename blockType>
BitArray<blockType> operator&(const BitArray<blockType>& b1, const BitArray<blockType>& b2) {
    auto res = BitArray<blockType>(b1);
    res &= b2;
    return res;
}

//Bitwise OR, returns new object
template<typename blockType>
BitArray<blockType> operator|(const BitArray<blockType>& b1, const BitArray<blockType>& b2) {
    auto res = BitArray<blockType>(b1);
    res |= b2;
    return res;
}

//Bitwise XOR, returns new object
template<typename blockType>
BitArray<blockType> operator^(const BitArray<blockType>& b1, const BitArray<blockType>& b2) {
    auto res = BitArray<blockType>(b1);
    res ^= b2;
    return res;
}

#endif /* BITARRAY_H */
