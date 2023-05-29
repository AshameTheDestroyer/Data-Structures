#include<iostream>

#ifndef LINKED_QUEUE
#define LINKED_QUEUE

#include "LinkedList.c++"

template<typename T>
class LinkedQueue : protected LinkedList<T>
{
public:
    /// @brief Creates a new empty Linked Queue.
    LinkedQueue() : LinkedList<T>() {}
    
    /// @brief Creates a new Linked Queue by copying another Linked Queue as reference.
    /// @param reference The reference of the Linked Queue that'll be copied.
    LinkedStack(const LinkedQueue<T> &reference)
    {
        for (Node<T>* currentNode = reference.head;
            currentNode; currentNode = currentNode->next)
        {
            if (!currentNode->isConstructed) { Add(currentNode); continue; }
            Add(currentNode->Data);
        }
    }

    ~LinkedQueue() = default;

public:
    /// @brief The amount of elements currently stored within the Linked Queue.
    /// @return The elements count of the Linked Queue.
    size_t Count() const { return ((LinkedList<T>*)this)->Count(); }
    
    /// @brief Indicates whether or not the Linked Queue has currently no elements.
    /// @return A boolean representing whether or not the Linked Queue is empty.
    bool IsEmpty() { return !((LinkedList<T>*)this)->Count(); }

    /// @brief Retrieves the element that is at the front of the Linked Queue, without removing it.
    /// @return The value of the element that is at the front of the Linked Queue.
    T Front() { return this->Tail()->Data; }

    /// @brief Retrieves the element that is at the back of the Linked Queue, without removing it.
    /// @return The value of the element that is at the back of the Linked Queue.
    T Back() { return this->Head()->Data; }

    /// @brief Adds an element to the front of the Linked Queue.
    /// @param element The value of the element that'll be added to the front of the Linked Queue.
    void Push(T element) { this->Add(element); }
    
    /// @brief Adds an Array to the front of the Linked Queue.
    /// @param array The Array that'll be added to the front of the Linked Queue.
    void PushRange(const Array<T> &array) { this->AddRange(array); }
    
    /// @brief Adds a range of elements to the front of the Linked Queue.
    /// @param length The amount of elements that'll be added to the front of the Linked Queue.
    /// @param data A pointer to an array in memory, that has some values that'll be added to the front of the Linked Queue.
    void PushRange(const size_t &length, T* data) { this->AddRange(length, data); }

    /// @brief Retrieves the element that is on the front of the Linked Queue, by removing it.
    /// @return The value of the element that is on the top of the Linked Queue.
    T Pop()
    {
        T lastElement = Back();
        this->RemoveAt(0);
        return lastElement;
    }
    
    /// @brief Adds an element to the front of the Linked Queue.
    /// @param element The value of the element that'll be added to the front of the Linked Queue.
    /// @return The reference of the Linked Queue after adding the element value to it.
    LinkedQueue<T> &operator<<(T element) { Push(element); return *this; }

    /// @brief Adds an Array to the front of the Linked Queue.
    /// @param array The Array that'll be added to the front of the Linked Queue.
    /// @return The reference of the Linked Queue after adding the element value to it.
    LinkedQueue<T> &operator<<(const Array<T> &array) { PushRange(array); return *this; }
};

#endif