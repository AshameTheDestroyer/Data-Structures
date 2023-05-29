#include<iostream>

#ifndef STACK
#define STACK

#include "DynamicArray.c++"

/// @brief A linear data structure to save data close together in memory as a pile, where
/// each element is put on top of the previous one, providing the First In Last Out functionality.
/// @tparam T The type of the data stored within the Stack.
template<typename T>
class Stack : protected DynamicArray<T>
{
public:
    /// @brief Creates a new empty Stack.
    Stack() : DynamicArray<T>() {}

    /// @brief Creates a new Stack with a defined capacity, to avoid copying the
    /// data if the initial capacity is known.
    /// @param capacity The amount of elements that'll be stored within the Stack.
    /// @param capacityModifier The amount of increment the Stack capacity gets each time it runs
    /// out of space to store more elements.
    explicit Stack(const size_t &capacity, const size_t capacityModifier = DynamicArray<T>::INITIAL_CAPACITY)
        : DynamicArray<T>(capacity, capacityModifier) { }

    /// @brief Creates a new Stack from a defined Array, and basically takes all of its data.
    /// @param array The Array that'll be used to create the Stack.
    /// @param capacityModifier The amount of increment the Stack capacity gets each time it runs
    /// out of space to store more elements.
    Stack(const Array<T> &array, const size_t capacityModifier = DynamicArray<T>::INITIAL_CAPACITY)
        : DynamicArray<T>(array, capacityModifier) { }

    /// @brief Creates a new Stack with a defined elements count and initial values.
    /// @param length The amount of elements that'll be stored within the Stack initially.
    /// @param data A pointer to an array in memory, that has some values that'll be
    /// stored within the Stack initially.
    /// @param capacityModifier The amount of increment the Stack capacity gets each time it runs
    /// out of space to store more elements.
    Stack(const size_t &length, T* data, const size_t capacityModifier = DynamicArray<T>::INITIAL_CAPACITY)
        : DynamicArray<T>(length, data, capacityModifier) { }

    ~Stack() = default;

public:
    /// @brief The amount of elements the Stack can maximally hold currently.
    /// @return The capacity of the Stack.
    size_t Capacity() const { return ((DynamicArray<T>*)this)->Capacity(); };
    /// @brief The amount of increment the Stack capacity gets each time it runs
    /// out of space to store more elements.
    /// @return The capacity modifier of the Stack.
    size_t CapacityModifier() const { return ((DynamicArray<T>*)this)->CapacityModifier(); }
    /// @brief The amount of elements currently stored within the Stack.
    /// @return The elements count of the Stack.
    size_t Count() const { return ((DynamicArray<T>*)this)->Count(); }

    /// @brief Indicates whether or not the Stack has currently no elements.
    /// @return A boolean representing whether or not the Stack is empty.
    bool IsEmpty() { return ((DynamicArray<T>*)this)->IsEmpty(); }

    /// @brief Retrieves the element that is on the top of the Stack, without removing it.
    /// @return The value of the element that is on the top of the Stack.
    T Top() { return *(this->end() - 1); }
    
    /// @brief Retrieves the element that is at the bottom of the Stack, without removing it.
    /// @return The value of the element that is at the bottom of the Stack.
    T Bottom() { return *(this->begin()); }
    
    /// @brief Adds an element on the top of the Stack.
    /// @param element The value of the element that'll be added on the top of the Stack.
    void Push(T element) { this->Add(element); }
    
    /// @brief Adds an Array on the top of the Stack.
    /// @param array The Array that'll be added on the top of the Stack.
    void PushRange(const Array<T> &array) { this->AddRange(array); }
    
    /// @brief Adds a range of elements on the top of the Stack.
    /// @param length The amount of elements that'll be added on the top of the Stack.
    /// @param data A pointer to an array in memory, that has some values that'll be added on the top of the Stack.
    void PushRange(const size_t &length, T* data) { this->AddRange(length, data); }

    /// @brief Retrieves the element that is on the top of the Stack, by removing it.
    /// @return The value of the element that is on the top of the Stack.
    T Pop()
    {
        T lastElement = Top();
        this->RemoveAt(this->count - 1);
        return lastElement;
    }
    
    /// @brief Adds an element on the top of the Stack.
    /// @param element The value of the element that'll be added on the top of the Stack.
    /// @return The reference of the Stack after adding the element value to it.
    Stack<T> &operator<<(T element) { Push(element); return *this; }
    
    /// @brief Adds an Array on the top of the Stack.
    /// @param array The Array that'll be added on the top of the Stack.
    /// @return The reference of the Stack after adding the element value to it.
    Stack<T> &operator<<(const Array<T> &array) { PushRange(array); return *this; }
};

#endif