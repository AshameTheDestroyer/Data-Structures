#include<iostream>

#ifndef LIST
#define LIST

#include "DynamicArray.c++"
#include "Array.c++"

/// @brief A data structure which is a dynamic array, that can be expanded up or shrunk
/// down by adding or removing elements from it, and offers more functionalities overall.
/// @tparam T The type of the data stored within the List.
template<typename T>
class List : public DynamicArray<T>
{
public:
    /// @brief Creates a new empty List.
    List() : DynamicArray<T>() { }

    /// @brief Creates a new List with a defined capacity, to avoid copying the
    /// data if the initial capacity is known.
    /// @param capacity The amount of elements that'll be stored within the List.
    /// @param capacityModifier The amount of increment the List capacity gets each time it runs
    /// out of space to store more elements.
    explicit List(const size_t &capacity, const size_t capacityModifier = DynamicArray<T>::INITIAL_CAPACITY)
        : DynamicArray<T>(capacity, capacityModifier) { }

    /// @brief Creates a new List from a defined Array, and basically takes all of its data.
    /// @param array The Array that'll be used to create the List.
    /// @param capacityModifier The amount of increment the List capacity gets each time it runs
    /// out of space to store more elements.
    List(const Array<T> &array, const size_t capacityModifier = DynamicArray<T>::INITIAL_CAPACITY)
        : DynamicArray<T>(array, capacityModifier) { }

    /// @brief Creates a new List with a defined elements count and intital values.
    /// @param length The amount of elements that'll be stored within the List initially.
    /// @param data A pointer to an array in memory, that has some values that'll be
    /// stored within the List initially.
    /// @param capacityModifier The amount of increment the List capacity gets each time it runs
    /// out of space to store more elements.
    List(const size_t &length, T* data, const size_t capacityModifier = DynamicArray<T>::INITIAL_CAPACITY)
        : DynamicArray<T>(length, data, capacityModifier) { }

    ~List() = default;

    /// @brief Searches for the first element in the List that matches a set of conditions.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @return The index of the first element that matches the set of conditions, or -1 if unfound.
    size_t First(std::function<bool(const T &element)> predicate) const { return this->array.First(predicate, this->count); }

    /// @brief Searches for the last element in the List that matches a set of conditions.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @return The index of the last element that matches the set of conditions, or -1 if unfound.
    size_t Last(std::function<bool(const T &element)> predicate) const { return this->array.Last(predicate, this->count); }

    /// @brief Searches for all the elements in the List that match a set of conditions.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @return An Array filled with all of the last elements indices that match the set of conditions,
    /// or an empty Array if unfound.
    Array<size_t> Every(std::function<bool(const T &element)> predicate) const { return this->array.Every(predicate, this->count); }

    /// @brief Checks if any of the List elements matches a set of conditions.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @return A boolean representing whether or not any of the Array elements matches the set of conditions.
    bool Any(std::function<bool(const T &element)> predicate) const { return this->array.Any(predicate, this->count); }

    /// @brief Checks if all of the List elements match a set of conditions.
    /// @param predicate A function that takes an element and validates it throughout a set of conditions.
    /// @return A boolean representing whether or not all of the Array elements match the set of conditions.
    bool All(std::function<bool(const T &element)> predicate) const { return this->array.All(predicate, this->count); }

    /// @brief Makes a copy of the List that'll have the same elements of this List, but
    /// in a reversed order.
    /// @return A List that has the same elements of this List but in a reversed order.
    List<T> Reverse() const { return List<T>(this->array.Reverse(this->count)); }

    /// @brief Adds an element to the end of the List.
    /// @param element The value of the element that'll be added to the List.
    /// @return The reference of the List after adding the element value to it.
    List<T> &operator<<(T element) { return (*this << element); }
    
    /// @brief Adds an Array of elements to the end of the List.
    /// @param array The Array that'll be added to the List.
    /// @return The reference of the List after adding the Array of elements value to it.
    List<T> &operator<<(const Array<T> &array) { return (*this << array); }
};

#endif