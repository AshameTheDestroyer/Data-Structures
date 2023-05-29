#include <iostream>

#ifndef LINK_STACK
#define LINK_STACK

#include "LinkedList.c++"

/// @brief A Linked-List-Based Stack.
/// @tparam T The type of the data stored within the Linked Stack.
template <typename T>
class LinkedStack : protected LinkedList<T>
{
public:
    /// @brief Creates a new empty Linked Stack.
    LinkedStack() : LinkedList<T>() {}

    /// @brief Creates a new Linked Stack by copying another Linked Stack as reference.
    /// @param reference The reference of the Linked Stack that'll be copied.
    LinkedStack(const LinkedStack<T> &reference)
    {
        for (Node<T>* currentNode = reference.head;
            currentNode; currentNode = currentNode->next)
        {
            if (!currentNode->isConstructed) { Add(currentNode); continue; }
            Add(currentNode->Data);
        }
    }

    ~LinkedStack() = default;

public:
    /// @brief The amount of elements currently stored within the Linked Stack.
    /// @return The elements count of the Linked Stack.
    size_t Count() const { return ((LinkedList<T> *)this)->Count(); }

    /// @brief Indicates whether or not the Linked Stack has currently no elements.
    /// @return A boolean representing whether or not the Linked Stack is empty.
    bool IsEmpty() { return !((LinkedList<T> *)this)->Count(); }

    /// @brief Retrieves the element that is on the top of the Linked Stack, without removing it.
    /// @return The value of the element that is on the top of the Linked Stack.
    T Top() { return this->Tail()->Data; }

    /// @brief Retrieves the element that is at the bottom of the Linked Stack, without removing it.
    /// @return The value of the element that is at the bottom of the Linked Stack.
    T Bottom() { return this->Head()->Data; }

    /// @brief Adds an element on the top of the Linked Stack.
    /// @param element The value of the element that'll be added on the top of the Linked Stack.
    void Push(T element) { this->Add(element); }

    /// @brief Adds an Array on the top of the Linked Stack.
    /// @param array The Array that'll be added on the top of the Linked Stack.
    void PushRange(const Array<T> &array) { this->AddRange(array); }

    /// @brief Adds a range of elements on the top of the Linked Stack.
    /// @param length The amount of elements that'll be added on the top of the Linked Stack.
    /// @param data A pointer to an array in memory, that has some values that'll be added on the top of the Linked Stack.
    void PushRange(const size_t &length, T *data) { this->AddRange(length, data); }

    /// @brief Retrieves the element that is on the top of the Linked Stack, by removing it.
    /// @return The value of the element that is on the top of the Linked Stack.
    T Pop()
    {
        T lastElement = Top();
        this->RemoveAt(this->Count() - 1, false);
        return lastElement;
    }

    /// @brief Adds an element on the top of the Linked Stack.
    /// @param element The value of the element that'll be added on the top of the Linked Stack.
    /// @return The reference of the Linked Stack after adding the element value to it.
    LinkedStack<T> &operator<<(T element)
    {
        Push(element);
        return *this;
    }

    /// @brief Adds an Array on the top of the Linked Stack.
    /// @param array The Array that'll be added on the top of the Linked Stack.
    /// @return The reference of the Linked Stack after adding the element value to it.
    LinkedStack<T> &operator<<(const Array<T> &array)
    {
        PushRange(array);
        return *this;
    }
};

#endif