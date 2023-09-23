#include <gtest/gtest.h>
#include "BitArray.h"
#include "BitArray.cpp"

TEST(BitArray, CopyConstructorTest) {
    auto b = BitArray<char>();
    for (int i = 0; i < 10; i++) {
        b.pushBack(true);
    }
    auto a = BitArray<char>(b);
    EXPECT_TRUE(a == b);
}

TEST(BitArray, Swap) {
    BitArray<char> b;
    for (int i = 0; i < 16; i++) {
        b.pushBack(true);
    }
    auto a = ~b;
    BitArray<char> old_b;
    old_b = b;
    a.swap(b);
    EXPECT_TRUE(~b == old_b);
}

TEST(BitArray, AnyNone) {
    auto b = BitArray<char>();
    for (int i = 0; i < 10; i++) {
        b.pushBack(false);
    }
    EXPECT_TRUE(b.none());
    b.set(9, true);
    EXPECT_TRUE(b.any());
}

TEST(BitArray, ResizeClear) {
    auto b = BitArray<char>(100);
    b.resize(20);
    EXPECT_EQ(b.size(), 20);
    b.clear();
    EXPECT_EQ(b.size(), 0);
}

TEST(BitArray, BitWiseToString) {
    auto b = BitArray<char>(8);
    for (int i = 0; i < b.size(); i += 2) {
        b.set(i, true);
    }
    auto a = ~b;
    auto resAnd = a & b;
    EXPECT_TRUE(resAnd.none());
    auto resOr = a | b;
    EXPECT_TRUE(resOr.to_string()[0] == char(255));
    auto resXor = a ^ b;
    EXPECT_TRUE(resOr == resXor);
    auto resNot = ~b;
    EXPECT_TRUE(a == resNot);
    a.reset();
    a.set(0, true);
    EXPECT_TRUE((a >> 2).to_string()[0] == char(32));
    a >>= 2;
    EXPECT_TRUE((a << 2).to_string()[0] == char(128));
    a <<= 2;
    a >>= 0;
    EXPECT_TRUE(a.to_string()[0] == char(128));
}

TEST(BitArray, Count) {
    auto a = BitArray<char>(100);
    a.reset();
    for (int i = 0; i < a.size(); i++) {
        if (i % 10 == 0) {
            a.set(i, true);
        }
    }
    EXPECT_EQ(a.count(), 10);
}

TEST(BitArray, EmptyReset) {
    BitArray<int> a;
    EXPECT_TRUE(a.empty());
    a.resize(32);
    a.set();
    EXPECT_EQ(a.count(), 32);
    a.reset();
    EXPECT_EQ(a.count(), 0);
}

TEST(BitArray, Exceptions) {
    BitArray<char> a(10);
    BitArray<char> b(100);
    EXPECT_ANY_THROW(b & a);
    EXPECT_ANY_THROW(b | a);
    EXPECT_ANY_THROW(b ^ a);
    EXPECT_ANY_THROW(a.swap(b));
    EXPECT_ANY_THROW(b[101]);
}
