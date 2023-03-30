#include<iostream>

#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include "Array.c++"
#include "HashTable.c++"

/// @brief Introduces the abstraction of the Hash Table class to the Dynamic Array class.
/// @tparam T The type of the data stored within the Sparse Array.
template<typename TKey, typename TValue>
class HashTable;

/// @brief A data structure which is a basic Array, that can be expanded up or shrunk
/// down by adding or removing elements from it.
/// @tparam T The type of the data stored within the Dynamic Array.
template<typename T>
class DynamicArray
{
public:
    /// @brief Makes the Hash Table class a friend with the Dynamic Array class.
    template<typename TKey, typename TValue>
    friend class HashTable;

    /// @brief Creates a new empty Dynamic Array.
    DynamicArray()
    {
        capacity = capacityModifier = INITIAL_CAPACITY;
        array = Array<T>(capacity);
    }

    /// @brief Creates a new Dynamic Array with a defined capacity, to avoid copying the
    /// data if the initial capacity is known.
    /// @param capacity The amount of elements that'll be stored within the Dynamic Array.
    /// @param capacityModifier The amount of increment the Dynamic Array capacity gets each time it runs
    /// out of space to store more elements.
    explicit DynamicArray(const size_t &capacity, const size_t capacityModifier = INITIAL_CAPACITY)
    {
        this->capacityModifier = capacityModifier;
        this->capacity = (capacity / capacityModifier + 1) * capacityModifier;
        array = Array<T>(this->capacity);
    }

    /// @brief Creates a new Dynamic Array from a defined Array, and basically takes all of its data.
    /// @param array The Array that'll be used to create the Dynamic Array.
    /// @param capacityModifier The amount of increment the Dynamic Array capacity gets each time it runs
    /// out of space to store more elements.
    DynamicArray(const Array<T> &array, const size_t capacityModifier = INITIAL_CAPACITY)
    {
        count = array.Length();
        this->capacityModifier = capacityModifier;
        capacity = (array.Length() / capacityModifier + 1) * capacityModifier;
        this->array = array.Resize(capacity);
    }

    /// @brief Creates a new Dynamic Array with a defined elements count and intital values.
    /// @param length The amount of elements that'll be stored within the Dynamic Array initially.
    /// @param data A pointer to an array in memory, that has some values that'll be
    /// stored within the Dynamic Array initially.
    /// @param capacityModifier The amount of increment the Dynamic Array capacity gets each time it runs
    /// out of space to store more elements.
    DynamicArray(const size_t &length, T* data, const size_t capacityModifier = INITIAL_CAPACITY)
        : DynamicArray(Array<T>(length, data), capacityModifier) { }

    ~DynamicArray() = default;

protected:
    /// @brief The amount of elements the Dynamic Array can maximumly hold currently.
    size_t capacity;
    /// @brief The amount of increment the Dynamic Array capacity gets each time it runs
    /// out of space to store more elements.
    size_t capacityModifier;
    /// @brief The amount of elements currently stored within the Dynamic Array.
    size_t count = 0;
    /// @brief The current Array that holds the current stored element.
    Array<T> array;

public:
    /// @brief The initial value of the Dynamic Array capacity modifier if unspecified by the consumer.
    static const size_t INITIAL_CAPACITY = 200;

    /// @brief The amount of elements the Dynamic Array can maximumly hold currently.
    /// @return The capacity of the Dynamic Array.
    size_t Capacity() const { return capacity; }
    /// @brief The amount of increment the Dynamic Array capacity gets each time it runs
    /// out of space to store more elements.
    /// @return The capacity modifier of the Dynamic Array.
    size_t CapacityModifier() const { return capacityModifier; }
    /// @brief The amount of elements currently stored within the Dynamic Array.
    /// @return The elements count of the Dynamic Array.
    size_t Count() const { return count; }

    /// @brief The beginning of the Dynamic Array.
    /// @return A pointer to the first element in the Dynamic Array.
    T* begin() const { return array.begin(); }
    /// @brief The end of the Dynamic Array.
    /// @return A pointer to the last element in the Dynamic Array.
    T* end() const { return array.begin() + count; }

    /// @brief Indicates whether or not the Dynamic Array has currently no elements.
    /// @return A boolean representing whether or not the Dynamic Array is empty.
    bool IsEmpty() { return !count; }

    /// @brief Adds an element to the end of the Dynamic Array.
    /// @param element The value of the element that'll be added to the Dynamic Array.
    void Add(T element)
    {
        ExpandArray(1);
        array[count - 1] = T(element);
    }

    /// @brief Adds an Array of elements to the end of the Dynamic Array.
    /// @param array The Array that'll be added to the Dynamic Array.
    void AddRange(const Array<T> &array)
    {
        ExpandArray(array.Length());

        for (size_t i = 0; i < array.Length(); i++)
        { this->array[i + count - array.Length()] = T(array[i]); }
    }

    /// @brief Adds a range of elements to the end of the Dynamic Array.
    /// @param length The amount of elements that'll be added to the Dynamic Array.
    /// @param data A pointer to an array in memory, that has some values that'll be added to the Dynamic Array.
    void AddRange(const size_t &length, T* data) { AddRange(Array<T>(length, data)); }

    /// @brief Adds an element into the Dynamic Array at a specified index.
    /// @param element The value of the element that'll be inserted into the Dynamic Array.
    /// @param index The order in which the desired element will be inserted at.
    void Insert(T element, const size_t &index) noexcept(false)
    {
        if (index == count || (!index && !count)) { Add(element); return; }

        ValidateBoundaries(index);
        Shift(index);

        array[index] = T(element);
    }

    /// @brief Adds an Array of elements into the Dynamic Array at a specified index.
    /// @param array The Array that'll be added to the Dynamic Array.
    /// @param index The order in which the desired Array will be inserted at.
    void InsertRange(const Array<T> &array, const size_t &index) noexcept(false)
    {
        if (index == count || (!index && !count)) { AddRange(array); return; }

        ValidateBoundaries(index);
        Shift(index, array.Length());

        for (size_t i = 0; i < array.Length(); i++)
        { this->array[i + index] = T(array[i]); }
    }

    /// @brief Adds a range of elements into the Dynamic Array at a specified index.
    /// @param length The amount of elements that'll be added to the Dynamic Array.
    /// @param data A pointer to an array in memory, that has some values that'll be added to the Dynamic Array.
    /// @param index The order in which the desired elements will be inserted at.
    void InsertRange(const size_t &length, T* data, const size_t &index) noexcept(false)
    { InsertRange(Array<T>(length, data), index); }
    
    /// @brief Searches for an element in the Dynamic Array, and returns its first occuring index.
    /// @param element The value of the desired element.
    /// @return The first occuring index of the element, or -1 if unfound.
    size_t FirstIndexOf(const T &element) const { return array.FirstIndexOf(element, count); }

    /// @brief Searches for an element in the Dynamic Array, and returns its last occuring index.
    /// @param element The value of the desired element.
    /// @return The last occuring index of the element, or -1 if unfound.
    size_t LastIndexOf(const T &element) const { return array.LastIndexOf(element, count); }

    /// @brief Searches for an element in the Dynamic Array, and returns all of its occuring indices.
    /// @param element The value of the desired element.
    /// @return An Array filled with all of the element occuring indices, or an empty Array if unfound.
    Array<size_t> IndicesOf(const T &element) const { return array.IndicesOf(element, count); }

    /// @brief Checks for the existence of an element in the Dynamic Array.
    /// @param element The value of the desired element.
    /// @return A boolean representing whether or not the element exists within the Dynamic Array.
    bool Contains(const T &element) const { return FirstIndexOf(element) != -1; }
    
    /// @brief Removes the first occurance of an element from the Dynamic Array.
    /// @param element The value of the desired element.
    /// @return A boolean representing whether or not the element has been removed.
    bool RemoveFirst(const T &element)
    {
        size_t index = FirstIndexOf(element);
        if (index == -1) { return false; }

        RemoveAt(index);
        return true;
    }

    /// @brief Removes the last occurance of an element from the Dynamic Array.
    /// @param element The value of the desired element.
    /// @return A boolean representing whether or not the element has been removed.
    bool RemoveLast(const T &element)
    {
        size_t index = LastIndexOf(element);
        if (index == -1) { return false; }

        RemoveAt(index);
        return true;
    }

    /// @brief Removes the all occurances of an element from the Dynamic Array.
    /// @param element The value of the desired element.
    /// @return A boolean representing whether or not the element has been removed.
    bool RemoveAll(const T &element)
    {
        Array<size_t> indices = IndicesOf(element);
        if (!indices.Length()) { return false; }

        for (auto &&index : indices)
        { RemoveAt(index); }
        
        return true;
    }

    /// @brief Removes an element from the Dynamic Array at a specified index.
    /// @param index The order in which the element will be removed from.
    void RemoveAt(const size_t &index) noexcept(false)
    {
        ValidateBoundaries(index);
        Unshift(index);
    }

    /// @brief Removes a range of elements from the Dynamic Array starting from a specified index.
    /// @param index The order in which the removal will start from.
    /// @param count The amount of elements will be removed.
    void RemoveRange(const size_t &index, const size_t &count) noexcept(false)
    {
        if (!this->count && !index && !count) { return; }

        ValidateBoundaries(index);
        ValidateBoundaries(index + count - 1);
        Unshift(index, count);
    }

    /// @brief Clears every element from the Dynamic Array.
    void Clear() { RemoveRange(0, count); }

    /// @brief Makes a copy of the Dynamic Array that'll have the same elements of this Dynamic Array, but
    /// in a reversed order.
    /// @return A Dynamic Array that has the same elements of this Dynamic Array but in a reversed order.
    DynamicArray<T> Reverse() const { return DynamicArray<T>(array.Reverse(count)); }

    // TODO: Sort Function Implementation.
    DynamicArray<T> Sort() const { return this; }

    /// @brief Converts the Dynamic Array into an Array.
    /// @return An Array consisting of all of the Dynamic Array elements.
    Array<T> ToArray() const { return array.Resize(count); }
    
    /// @brief Gets or Sets an element in the Dynamic Array.
    /// @param index The order of the desired element.
    /// @return The element.
    T &operator[](const size_t &index) noexcept(false)
    {
        ValidateBoundaries(index);
        return array[index];
    }

    /// @brief Only Gets an element in the Dynamic Array, without the ability to Set it.
    /// @param index The order of the desired element.
    /// @return The value of the element.
    T operator[](const size_t &index) const noexcept(false)
    {
        ValidateBoundaries(index);
        return array[index];
    }

    /// @brief Adds an element to the end of the Dynamic Array.
    /// @param element The value of the element that'll be added to the Dynamic Array.
    /// @return The reference of the Dynamic Array after adding the element value to it.
    DynamicArray<T> &operator<<(T element) { Add(element); return *this; }
    
    /// @brief Adds an Array of elements to the end of the Dynamic Array.
    /// @param array The Array that'll be added to the Dynamic Array.
    /// @return The reference of the Dynamic Array after adding the Array of elements value to it.
    DynamicArray<T> &operator<<(const Array<T> &array) { AddRange(array); return *this; }

protected:
    /// @brief Checks whether or not an index is within the boundaries of the Dynamic Array, if not,
    /// it'll throw an "out of range" exception.
    /// @param index The selected index that'll be checked.
    void ValidateBoundaries(const size_t &index) const noexcept(false)
    {
        if (index < count) { return; }

        throw std::out_of_range("The index [" + std::to_string(index) + "] is out of the range of the Dynamic Array.");
    }

    /// @brief Expands the elements count of the Dynamic Array, and also expands the capacity if necessary.
    /// @param count The amount of elements the Dynamic Array will be expanded to store.
    void ExpandArray(const size_t &count)
    {
        this->count += count;
        if (this->count > capacity)
        {
            capacity = (this->count / capacityModifier + 1) * capacityModifier;
            array = array.Resize(capacity);
        }
    }

    /// @brief Shifts all the elements starting at an index towards the right by a specified
    /// amount of steps.
    /// @param start The index of which the shifting will start at.
    /// @param steps The amount of steps the shifting will go towards the right.
    void Shift(const size_t &start, const size_t &steps = 1)
    {
        ExpandArray(steps);

        for (size_t i = count - steps - 1; i >= (size_t)start; i--)
        {
            array[i + steps] = array[i];
            if (!i) { break; }
        }
    }

    /// @brief Shifts all the elements starting at an index towards the left by a specified
    /// amount of steps.
    /// @param start The index of which the shifting will start at.
    /// @param steps The amount of steps the shifting will go towards the left.
    void Unshift(const size_t &start, const size_t &steps = 1)
    {
        for (size_t i = start + steps; i < count; i++)
        { array[i - steps] = array[i]; }

        count -= steps;
    }
};

#endif