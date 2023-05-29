#include<iostream>

#ifndef ARRAY
#define ARRAY

/// @brief Introduces the abstraction of the Dynamic Array class to the Array class.
/// @tparam T The type of the data stored within the Dynamic Array.
template<typename T>
class DynamicArray;

/// @brief Introduces the abstraction of the List class to the Array class.
/// @tparam T The type of the data stored within the List.
template<typename T>
class List;

/// @brief A linear data structure to save data close together in memory.
/// @tparam T The type of the data stored within the Array.
template<typename T>
class Array
{
public:
    /// @brief Makes the Dynamic Array class a friend with the Array class.
    friend class DynamicArray<T>;

    /// @brief Creates a new empty Array.
    Array() = default;

    /// @brief Creates a new Array with a defined length, and all elements are set to
    /// their default value.
    /// @param length The amount of elements that'll be stored within the Array.
    explicit Array(const size_t &length) : data(new T[length]), length(length) { }

    /// @brief Creates a new Array with a defined length, and all elements are set to
    /// an initial value.
    /// @param length The amount of elements that'll be stored within the Array.
    /// @param initialValue The value that'll be set to each element as a default one.
    Array(const size_t &length, const T &initialValue) : Array(length)
    {
        for (size_t i = 0; i < length; i++)
        { data[i] = T(initialValue); }
    }

    /// @brief Creates a new Array with a defined length and initial values.
    /// @param length The amount of elements that'll be stored within the Array.
    /// @param data A pointer to an array in memory, that has some values that'll be
    /// stored within the Array.
    Array(const size_t &length, T* data) : Array(length) { this->data = data; }

    /// @brief Creates a new Array by copying another Array as reference.
    /// @param reference The reference of the Array that'll be copied.
    Array(const Array<T> &reference)
    {
        data = new T[length = reference.length];
        for (size_t i = 0; i < reference.length; i++)
        { data[i] = T(reference.data[i]); }
    }
    
    ~Array()
    {
        if (data == nullptr) { return; }
        delete[] data;
        data = nullptr;
    }

private:
    /// @brief The amount of elements stored within the Array.
    size_t length = 0;
    /// @brief A pointer to the first element in the Array.
    T* data = nullptr;

public:
    /// @brief The amount of elements stored within the Array.
    /// @return The length of the Array.
    size_t Length() const { return length; }

    /// @brief The beginning of the Array.
    /// @return A pointer to the first element in the Array.
    T* begin() const { return data; }
    /// @brief The end of the Array.
    /// @return A pointer to the last element in the Array.
    T* end() const { return data + length; }
    
    /// @brief Searches for an element in the Array, and returns its first occuring index.
    /// @param element The value of the desired element.
    /// @return The first occuring index of the element, or -1 if unfound.
    size_t FirstIndexOf(const T &element) const { return FirstIndexOf(element, length); }

    /// @brief Searches for an element in the Array, and returns its last occuring index.
    /// @param element The value of the desired element.
    /// @return The last occuring index of the element, or -1 if unfound.
    size_t LastIndexOf(const T &element) const { return LastIndexOf(element, length); }

    /// @brief Searches for an element in the Array, and returns all of its occuring indices.
    /// @param element The value of the desired element.
    /// @return An Array filled with all of the element occuring indices, or an empty Array if unfound.
    Array<size_t> IndicesOf(const T &element) const { return IndicesOf(element, length); }

    /// @brief Checks for the existence of an element in the Array.
    /// @param element The value of the desired element.
    /// @return A boolean representing whether or not the element exists within the Array.
    bool Contains(const T &element) const { return FirstIndexOf(element) != -1; }

    /// @brief Searches for the first element in the Array that matches a set of conditions.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @return The index of the first element that matches the set of conditions, or -1 if unfound.
    size_t First(std::function<bool(const T &element)> predicate) const { return First(predicate, length); }

    /// @brief Searches for the last element in the Array that matches a set of conditions.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @return The index of the last element that matches the set of conditions, or -1 if unfound.
    size_t Last(std::function<bool(const T &element)> predicate) const { return Last(predicate, length); }

    /// @brief Searches for all the elements in the Array that match a set of conditions.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @return An Array filled with all of the last elements indices that match the set of conditions,
    /// or an empty Array if unfound.
    Array<size_t> Every(std::function<bool(const T &element)> predicate) const { return Every(predicate, length); }

    /// @brief Checks if any of the Array elements matches a set of conditions.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @return A boolean representing whether or not any of the Array elements matches the set of conditions.
    bool Any(std::function<bool(const T &element)> predicate) const { return Any(predicate, length); }

    /// @brief Checks if all of the Array elements match a set of conditions.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @return A boolean representing whether or not all of the Array elements match the set of conditions.
    bool All(std::function<bool(const T &element)> predicate) const { return All(predicate, length); }

    /// @brief Makes a copy of the Array with a new length.
    /// @param length The amount of elements is going to be stored within the array.
    /// @return A copy of the new resized Array.
    Array<T> Resize(const size_t &length) const
    {
        Array<T> resizedArray(length);
        for (size_t i = 0; i < std::min(this->length, length); i++)
        { resizedArray.data[i] = data[i]; }
        
        return resizedArray;
    }

    /// @brief Makes a copy of the Array with a new length.
    /// @param length The amount of elements is going to be stored within the array.
    /// @param defaultValue The value that'll be set to each element that got initialized without
    /// a copied value.
    /// @return A copy of the new resized Array.
    Array<T> Resize(const size_t &length, const T &defaultValue) const
    {
        Array<T> resizedArray = Resize(length);
        if (length <= length) { goto FINISH; }

        for (size_t i = length; i < length; i++)
        { resizedArray.data[i] = T(defaultValue); }
        
        FINISH: return resizedArray;
    }
    
    /// @brief Makes a copy of the Array that'll have the same elements of this Array, but
    /// in a reversed order.
    /// @return An Array that has the same elements of this Array but in a reversed order.
    Array<T> Reverse() const { return Reverse(length); }

    // TODO: Sort Function Implementation.
    Array<T> Sort() const { return this; }

    /// @brief Converts the Array into a Dynamic Array.
    /// @return A Dynamic Array containing all of the Array elements.
    DynamicArray<T> ToDynamicArray() const { return DynamicArray<T>(*this); }

    /// @brief Converts the Array into a List.
    /// @return A List containing all of the Array elements.
    List<T> ToList() const { return List<T>(*this); }

    /// @brief Copies an Array into another.
    /// @param reference The reference of the Array that'll be copied.
    /// @return The result of the copying.
    Array<T> &operator=(const Array<T> &reference)
    {
        if (this == &reference) { return *this; }

        if (data != nullptr) { delete[] data; }
        data = new T[length = reference.length];

        for (size_t i = 0; i < reference.length; i++)
        { data[i] = T(reference.data[i]); }
        
        return *this;
    }

    /// @brief Gets or Sets an element in the Array.
    /// @param index The order of the desired element.
    /// @return The element.
    T &operator[](const size_t &index) noexcept(false)
    {
        ValidateBoundaries(index);
        return data[index];
    }

    /// @brief Only Gets an element in the Array, without the ability to Set it.
    /// @param index The order of the desired element.
    /// @return The value of the element.
    T operator[](const size_t &index) const noexcept(false)
    {
        ValidateBoundaries(index);
        return data[index];
    }

private:
    /// @brief Checks whether or not an index is within the boundaries of the Array, if not,
    /// it'll throw an "out of range" exception.
    /// @param index The selected index that'll be checked.
    void ValidateBoundaries(const size_t &index) const noexcept(false)
    {
        if (index < length) { return; }

        throw std::out_of_range("The index [" + std::to_string(index) + "] is out of the range of the Array.");
    }

    /// @brief Searches for an element in the Array to a specified ending, and returns its first occuring index.
    /// @param element The value of the desired element.
    /// @param end The index in which the search will end at.
    /// @return The first occuring index of the element, or -1 if unfound.
    size_t FirstIndexOf(const T &element, const size_t &end) const
    { return First([&](const T &element_) { return element_ == element; }, end); }

    /// @brief Searches for an element in the Array to a specified ending, and returns its last occuring index.
    /// @param element The value of the desired element.
    /// @param end The index in which the search will end at.
    /// @return The last occuring index of the element, or -1 if unfound.
    size_t LastIndexOf(const T &element, const size_t &end) const
    { return Last([&](const T &element_) { return element_ == element; }, end); }

    /// @brief Searches for an element in the Array to a specified ending, and returns all of its occuring indices.
    /// @param element The value of the desired element.
    /// @param end The index in which the search will end at.
    /// @return An Array filled with all of the element occuring indices, or an empty Array if unfound.
    Array<size_t> IndicesOf(const T &element, const size_t &end) const
    { return Every([&](const T &element_) { return element_ == element; }, end); }

    /// @brief Searches for the first element in the Array that matches a set of conditions to a specified ending.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @param end The index in which the search will end at.
    /// @return The index of the first element that matches the set of conditions, or -1 if unfound.
    size_t First(std::function<bool(const T &element)> predicate, const size_t &end) const
    {
        for (size_t i = 0; i < std::min(length, end); i++)
        { if (predicate(data[i])) { return i; } }

        return -1;
    }

    /// @brief Searches for the last element in the Array that matches a set of conditions to a specified ending.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @param end The index in which the search will end at.
    /// @return The index of the last element that matches the set of conditions, or -1 if unfound.
    size_t Last(std::function<bool(const T &element)> predicate, const size_t &end) const
    {
        for (size_t i = std::min(length, end) - 1; i >= 0; i--)
        { if (predicate(data[i])) { return i; } }

        return -1;
    }

    /// @brief Searches for all the elements in the Array that match a set of conditions to a specified ending.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @param end The index in which the search will end at.
    /// @return An Array filled with all of the last elements indices that match the set of conditions,
    /// or an empty Array if unfound.
    Array<size_t> Every(std::function<bool(const T &element)> predicate, const size_t &end) const
    {
        size_t indicesCount = 0;
        Array<size_t> indices(std::min(length, end));
        
        for (size_t i = 0; i < std::min(length, end); i++)
        { if (predicate(data[i])) { indices[indicesCount++] = i; } }

        return indices.Resize(indicesCount);
    }

    /// @brief Checks if any of the Array elements matches a set of conditions to a specified ending.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @param end The index in which the checking will end at.
    /// @return A boolean representing whether or not any of the Array elements matches the set of conditions.
    bool Any(std::function<bool(const T &element)> predicate, const size_t &end) const
    { return First(predicate, end) != -1; }

    /// @brief Checks if all of the Array elements match a set of conditions to a specified ending.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @param end The index in which the checking will end at.
    /// @return A boolean representing whether or not all of the Array elements match the set of conditions.
    bool All(std::function<bool(const T &element)> predicate, const size_t &end) const
    {
        for (size_t i = 0; i < std::min(length, end); i++)
        { if (!predicate(data[i])) { return false; } }
        
        return true;
    }

    /// @brief Makes a copy of the Array that'll have the same elements of this Array, but
    /// in a reversed order, to a specified ending.
    /// @param end The index in which the reversing will end at.
    /// @return An Array that has the same elements of this Array but in a reversed order.
    Array<T> Reverse(const size_t &end) const
    {
        size_t newLength = std::min(length, end);
        Array<T> reversedArray(newLength);

        for (size_t i = 0; i < newLength; i++)
        { reversedArray.data[i] = T(data[newLength - i - 1]); }

        return reversedArray;
    }
};

/// @brief Simple shortcut of writing Two-Dimensional Array types.
/// @tparam T The type of the data stored within the Matrix.
template<typename T>
using Matrix = Array<Array<T>>;

/// @brief Simple shortcut of writing Three-Dimensional Array types.
/// @tparam T The type of the data stored within the Tensor.
template<typename T>
using Tensor = Array<Array<Array<T>>>;

#endif