#include<iostream>

#ifndef HASH_TABLE
#define HASH_TABLE

#include "LinkedList.c++"
#include "List.c++"

#include "Algorithms/MurmurHashingAlgorithm.c++"

/// @brief A data structure where every entry consists of a key and a valuel, where the key
/// can be used to access its associated value.
/// @tparam TKey 
/// @tparam TValue 
template<typename TKey, typename TValue>
class HashTable
{
public:
    /// @brief Creates a new empty Hash Table.
    HashTable()
    {   
        this->threshold = INITIAL_THRESHOLD;

        keys = List<LinkedList<TKey>>();
        values = List<LinkedList<TValue>>();
    }

    /// @brief Creates a new Hash Table with a defined capacity, to avoid copying the
    /// data if the initial capacity is known.
    /// @param capacity The amount of elements that'll be stored within the Hash Table.
    /// @param threshold The percentage of the Hash Table that needs to be occupied before resizing.
    /// @param capacityModifier The amount of increment the Hash Table capacity gets each time it runs
    /// out of space to store more elements.
    /// @param hashingAlgorith The algorithm that'll be used to hash the keys of the Hash Table,
    /// (if none's given, the built-in MurmurHash algorithm will be used instead).
    /// @param hashingSeed An initial value that determines the outcome of the given hashing algorithm,
    /// (usually, it's set to zero).
    HashTable(const size_t &capacity, float threshold = HashTable<TKey, TValue>::INITIAL_THRESHOLD,
        const size_t capacityModifier = HashTable<TKey, TValue>::INITIAL_CAPACITY,
        std::function<long(const long &rawHashing, const long &seed)> hashingAlgorithm = MurmurHashingAlgorithm,
        const long &hashingSeed = 0)
    {
        this->threshold = threshold;
        ValidateThreshold();

        keys = List<LinkedList<TKey>>(capacity, capacityModifier);
        values = List<LinkedList<TValue>>(capacity, capacityModifier);

        this->HashingAlgorithm = hashingAlgorithm;
        this->hashingSeed = hashingSeed;
    }
    
private:
    /// @brief The keys stored within the Hash Table.
    List<LinkedList<TKey>> keys;
    /// @brief The values stored within the Hash Table.
    List<LinkedList<TValue>> values;
    /// @brief The percentage of the Hash Table that needs to be occupied before resizing.
    float threshold;
    /// @brief The algorithm that'll be used for hashing the keys of the Hash Table.
    std::function<long(const long &rawHashing, const long &seed)> HashingAlgorithm = MurmurHashingAlgorithm;
    /// @brief The initial value that determines the outcome of the given hashing algorithm.
    long hashingSeed = 0;
    /// @brief The amount of pairs that got hashed into the Hashed Table.
    long hashedPairCount = 0;
    
public:
    /// @brief The initial value of the Hash Table capacity modifier if unspecified by the consumer.
    static constexpr float INITIAL_THRESHOLD = 0.75F;
    /// @brief The initial value of the Hash Table capacity modifier if unspecified by the consumer.
    static const size_t INITIAL_CAPACITY = 500;

    /// @brief The amount of elements the Dynamic Array can maximally hold currently.
    /// @return The capacity of the Dynamic Array.
    size_t Capacity() const { return keys.capacity; }
    /// @brief The amount of increment the Dynamic Array capacity gets each time it runs
    /// out of space to store more elements.
    /// @return The capacity modifier of the Dynamic Array.
    size_t CapacityModifier() const { return keys.capacityModifier; }
    /// @brief The percentage of the Hash Table that needs to be occupied before resizing.
    /// @return The threshold of the Hash Table.
    float Threshold() const { return threshold; }

    // TODO: An overloading for the value TKey types, using Sorted Set and Binary Search.

    /// @brief Sets a pair within the Hash Table.
    /// @param key The key of the pair that'll be used to access the value its associated with.
    /// @param value The value that'll be associated with the key.
    void Set(TKey &key, TValue value)
    {
        long rawHashing = long(&key) + long(&key) + sizeof(key),
            hashingValue = HashingAlgorithm(rawHashing, hashingSeed);
        size_t index = hashingValue % values.capacity;
        
        LinkedList<TKey>* keyPocket = &keys.array[index];
        LinkedList<TValue>* valuePocket = &values.array[index];
        
        Node<TKey>* keyNode = keyPocket->FindFirstNode(key);
        if (keyNode == nullptr)
        {
            keyPocket->Add(key);
            valuePocket->Add(value);
            
            hashedPairCount++;
            return;
        }

        size_t keyNodeIndex = keyPocket->IndexOf(keyNode);
        valuePocket->NodeAt(keyNodeIndex)->Data = value;
    }

    /// @brief Gets a value within the Hash Table using a key, (if the key doesn't exist, it'll throw
    /// an "out of range" exception).
    /// @param key The key of the pair that'll be used to access the value its associated with.
    /// @return The value that's associated with the key.
    TValue Get(TKey &key)
    {
        long rawHashing = long(&key) + long(&key) + sizeof(key),
            hashingValue = HashingAlgorithm(rawHashing, hashingSeed);
        size_t index = hashingValue % values.capacity;
        
        LinkedList<TKey>* keyPocket = &keys.array[index];
        LinkedList<TValue>* valuePocket = &values.array[index];
        
        auto keyNode = keyPocket->FindFirstNode(key);
        if (keyNode != nullptr)
        {
            size_t keyNodeIndex = keyPocket->IndexOf(keyNode);
            return valuePocket->NodeAt(keyNodeIndex)->Data;
        }

        throw std::out_of_range("The provided key doesn't exist within the Hash Table.");
    }

    /// @brief Checks for a key within the Hash Table.
    /// @param key The key of the pair that'll be searched for.
    /// @return A boolean value representing whether or not the key is presented in the Hash Table.
    bool Has(TKey &key)
    {
        try { Get(key); return true; } catch (...) { }
        return false;
    }

    /// @brief Gets or Sets a value within the Hash Table using a key, without the ability
    /// to set it, (if the key doesn't exist, it'll throw an "out of range" exception).
    /// @param key The key of the pair that'll be used to access the value its associated with.
    /// @return The value that's associated with the key.
    TValue operator[](const TKey &key) const noexcept(false)
    { return Get(key); }
    
private:
    /// @brief Checks whether or not the threshold is between 0 and 1, if not,
    /// it'll throw an "out of range" exception.
    void ValidateThreshold() const
    {
        if (0 < threshold && threshold <= 1) { return; }

        throw std::out_of_range("The threshold [" + std::to_string(threshold) + "] is out of the range of [0, 1).");
    }

    /// @brief Checks if the Hash Table is up to its threshold percentage, and adapte to
    /// a new capacity if needed.
    void AdapteCapacity()
    {
        // TODO: Finish implementing this.
        if (hashedPairCount / (float)keys.capacity < threshold) { return; }

        // std::cout << "UPDATED TO ";

        keys.ExpandArray(keys.capacityModifier);
        values.ExpandArray(keys.capacityModifier);
    }
};

#endif