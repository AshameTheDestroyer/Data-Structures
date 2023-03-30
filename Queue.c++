#include<iostream>

#ifndef QUEUE
#define QUEUE

#include "DynamicArray.c++"

template<typename T>
class Queue : protected DynamicArray<T>
{
public:
    /// @brief Creates a new empty Queue.
    Queue() : DynamicArray<T>() { }

    /// @brief Creates a new Queue with a defined capacity, to avoid copying the
    /// data if the initial capacity is known.
    /// @param capacity The amount of elements that'll be stored within the Queue.
    /// @param capacityModifier The amount of increment the Queue capacity gets each time it runs
    /// out of space to store more elements.
    explicit Queue(const size_t &capacity, const size_t capacityModifier = DynamicArray<T>::INITIAL_CAPACITY)
        : DynamicArray<T>(capacity, capacityModifier) { }

    /// @brief Creates a new Queue from a defined Array, and basically takes all of its data.
    /// @param array The Array that'll be used to create the Queue.
    /// @param capacityModifier The amount of increment the Queue capacity gets each time it runs
    /// out of space to store more elements.
    Queue(const Array<T> &array, const size_t capacityModifier = DynamicArray<T>::INITIAL_CAPACITY)
        : DynamicArray<T>(array, capacityModifier) { }

    /// @brief Creates a new Queue with a defined elements count and intital values.
    /// @param length The amount of elements that'll be stored within the Queue initially.
    /// @param data A pointer to an array in memory, that has some values that'll be
    /// stored within the Queue initially.
    /// @param capacityModifier The amount of increment the Queue capacity gets each time it runs
    /// out of space to store more elements.
    Queue(const size_t &length, T* data, const size_t capacityModifier = DynamicArray<T>::INITIAL_CAPACITY)
        : DynamicArray<T>(length, data, capacityModifier) { }

    ~Queue() = default;

    /// @brief The amount of elements the Queue can maximumly hold currently.
    /// @return The capacity of the Queue.
    size_t Capacity() const { return ((DynamicArray<T>*)this)->Capacity(); };
    /// @brief The amount of increment the Queue capacity gets each time it runs
    /// out of space to store more elements.
    /// @return The capacity modifier of the Queue.
    size_t CapacityModifier() const { return ((DynamicArray<T>*)this)->CapacityModifier(); }
    /// @brief The amount of elements currently stored within the Queue.
    /// @return The elements count of the Queue.
    size_t Count() const { return ((DynamicArray<T>*)this)->Count(); }
    
    /// @brief Indicates whether or not the Queue has currently no elements.
    /// @return A boolean representing whether or not the Queue is empty.
    bool IsEmpty() { return ((DynamicArray<T>*)this)->IsEmpty(); }

    /// @brief Retrieves the element that is at the front of the Queue, without removing it.
    /// @return The value of the element that is at the front of the Queue.
    T Front() { return *(this->end() - 1); }

    /// @brief Retrieves the element that is at the back of the Queue, without removing it.
    /// @return The value of the element that is at the back of the Queue.
    T Back() { return *(this->begin()); }

    /// @brief Adds an element to the front of the Queue.
    /// @param element The value of the element that'll be added to the front of the Queue.
    void Push(T element) { this->Add(element); }
    
    /// @brief Adds an Array to the front of the Queue.
    /// @param array The Array that'll be added to the front of the Queue.
    void PushRange(const Array<T> &array) { this->AddRange(array); }
    
    /// @brief Adds a range of elements to the front of the Queue.
    /// @param length The amount of elements that'll be added to the front of the Queue.
    /// @param data A pointer to an array in memory, that has some values that'll be added to the front of the Queue.
    void PushRange(const size_t &length, T* data) { this->AddRange(length, data); }

    /// @brief Retrieves the element that is on the front of the Queue, by removing it.
    /// @return The value of the element that is on the top of the Queue.
    T Pop()
    {
        T lastElement = Back();
        this->RemoveAt(0);
        return lastElement;
    }
    
    /// @brief Adds an element to the front of the Queue.
    /// @param element The value of the element that'll be added to the front of the Queue.
    /// @return The reference of the Queue after adding the element value to it.
    Queue<T> &operator<<(T element) { Push(element); return *this; }

    /// @brief Adds an Array to the front of the Queue.
    /// @param array The Array that'll be added to the front of the Queue.
    /// @return The reference of the Queue after adding the element value to it.
    Queue<T> &operator<<(const Array<T> &array) { PushRange(array); return *this; }
};

#endif