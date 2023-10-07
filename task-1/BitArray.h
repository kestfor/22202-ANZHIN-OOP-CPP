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

    /**
     * @return index of last unused byte
     */
    [[nodiscard]] int lastUnusedByteInd() const;

    /**
     * reallocates array memory, changes current size, capacity, throw range error if numbits < 0
     * @param numBits
     */
    void reallocateArray(int numBits);

    //proxy class for item assignment
    class Bit {
    private:
         //original array of BitArray
        BitArray<blockType> *bitArray;

        int index;

    public:
        bool value;

        Bit(BitArray<blockType> *bitArray, int ind);

        Bit(const Bit &b);

        Bit &operator=(bool val);

        Bit &operator=(const Bit &other);

        operator bool() {
            return this->value;
        }
    };

public:

    //creates empty array reserving memory with size of one 'blockType'
    BitArray();

    //clears allocated memory
    ~BitArray();

    /**
     * creates array with size of numbits, first size of 'blockType' bytes initialises as 'value'
     * @param numBits
     * @param value
     */
    explicit BitArray(int numBits, blockType value = 0);

    //copy constructor
    BitArray(const BitArray &b);

    //swaps two arrays, throw runtime error if sizes are not equal
    void swap(BitArray &other);

    //operator[] analogue, works 2 times faster due to work without Bit class, it is preferable to use when you need to read a bit
    bool get(int ind) const {
        if (ind < 0 || ind >= currSizeInBites || currSizeInBites == 0) {
            throw std::out_of_range("invalid index");
        } else {
            int byteNum = ind / 8;
            int bitNum = ind % 8;
            return (*((byte *) this->array + byteNum)) & (1 << (7 - bitNum));
        }
    }

    //copies other's array bits, resizes array if needed
    BitArray& operator=(const BitArray& other);

    /**
     * changes size of array to numbits, if new size bigger, then new bits initialises as 'value', throw range error if numbits < 0
     * @param numBits
     * @param value
     */
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

    /**
     * sets bit at index n to the value = 'val', throw range error if index out of range
     * @param n
     * @param val
     * @return reference to BitArray
     */
    BitArray& set(int n, bool val = true);

    //sets all bits to the 1
    BitArray& set();

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

    //returns/sets value of bit at 'i' index, throw range error if index out of range
    Bit operator[](int i);

    //returns amount of bits, used in array
    int size() const;

    //returns true if size is 0
    bool empty() const;

    //turn every byte to char, returns string of this chars
    std::string toString() const;
};


//returns true if arrays are equal
template<typename blockType>
bool operator==(const BitArray<blockType> & a, const BitArray<blockType> & b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); i++) {
        if (a.get(i) != b.get(i)) {
            return false;
        }
    }
    return true;
}

template<typename blockType>
bool operator!=(const BitArray<blockType> & a, const BitArray<blockType> & b) {
    return !(a == b);
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

/**
 * @tparam blockType
 * @param first_bit
 * @param second_bit
 * @return true if objects represents equal bits
 */
template<typename blockType>
bool operator==(const typename BitArray<blockType>::Bit &a, const typename BitArray<blockType>::Bit &b) {
    return a.value == b.value;
}

/**
 *
 * @tparam blockType
 * @param first_bit
 * @param second_bit
 * @return true if objects represents not equal bits
 */
template<typename blockType>
bool operator!=(const typename BitArray<blockType>::Bit &a, const typename BitArray<blockType>::Bit &b) {
    return !(a.value == b.value);
}

#endif /* BITARRAY_H */
