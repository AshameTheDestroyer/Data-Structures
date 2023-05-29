#include<iostream>

#ifndef MURMUR_HASHING_ALGORITHM
#define MURMUR_HASHING_ALGORITHM

#include "../Array.c++"

/// @brief Converts a decimal number into a binary number.
/// @param value The value of the given number.
/// @return A string representing the value of the specified number but in binary.
std::string ToBinary(long value)
{
    const short BASE = 2;
    std::string binaryValue = "";
    while (value)
    {
        binaryValue = std::to_string(value % BASE) + binaryValue;
        value /= BASE;
    }
    return binaryValue;
}

/// @brief Converts a binary number into a decimal number.
/// @param value The value of the given number as a string.
/// @return A number representing the value of the specified number but in decimal.
long ToDecimal(const std::string &value)
{
    long decimalValue = 0;
    for (size_t i = 0; i < value.size(); i++)
    { decimalValue += (value[i] - '0') * std::pow(2, value.size() - i - 1); }
    return decimalValue;
}

/// @brief Converts a number into an Array of bytes.
/// @param value The value of the given number.
/// @return An Array that contains every byte of the specified number.
Array<short> ToByteArray(const long &value)
{
    std::string binaryValue = ToBinary(value);

    const short BIT_COUNT_IN_BYTE = 4;
    short byteCount = std::ceil(binaryValue.length() / (float)BIT_COUNT_IN_BYTE);
    auto bytes = Array<short>(byteCount);

    for (size_t i = 0; i < byteCount; i++)
    {
        std::string byteChunk = binaryValue.substr(i * BIT_COUNT_IN_BYTE, BIT_COUNT_IN_BYTE);
        bytes[i] = ToDecimal(byteChunk);
    }
    return bytes;
}

/// @brief Takes a raw hashing value and hash it properly using the Murmur Hashing Algorithm way.
/// @param rawHashing The raw value before it gets hashed properly.
/// @param seed The initial value that determines the outcome of the hashing algorithm.
/// @return A properly hashed value.
long MurmurHashingAlgorithm(const long &rawHashing, const long &seed = 0)
{
    const long PRIME = 2003, SHIFTING_RATE = 24;

    long hashValue = seed ^ std::to_string(rawHashing).length();
    auto bytes = ToByteArray(rawHashing);

    for (auto &&byte : bytes)
    {
        byte = (byte * PRIME) & LONG_MAX;
        byte ^= (byte >> SHIFTING_RATE);

        byte = (byte * PRIME) & LONG_MAX;
        hashValue = (hashValue * PRIME) & LONG_MAX;

        hashValue ^= byte;
    }

    hashValue ^= (hashValue >> SHIFTING_RATE);
    hashValue = (hashValue * PRIME) & LONG_MAX;
    hashValue ^= (hashValue >> SHIFTING_RATE);
    
    return hashValue;
}

#endif