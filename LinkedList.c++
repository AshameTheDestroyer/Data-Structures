#include<iostream>

#ifndef LINKED_LIST
#define LINKED_LIST

#include "Node.c++"
#include "List.c++"
#include "Array.c++"

/// @brief Introduces the abstraction of the Sparse Array class to the Linked List class.
/// @tparam T The type of the data stored within the Sparse Array.
template<typename T>
class SparseArray;

/// @brief A data structure which is a set of incontiguous Nodes, that can be expanded up or shrunk
/// down by adding or removing Nodes from it.
/// @tparam T The type of the data stored within the Linked List.
template<typename T>
class LinkedList
{
public:
    /// @brief Makes the Sparse Array class a friend with the Linked List class.
    friend class SparseArray<T>;

    /// @brief Creates a new empty Linked List.
    /// @param improvableSearch Determines whether or not the Linked List will improve its
    /// searching each time it searches for a Node or a value within.
    explicit LinkedList(const bool &improvableSearch = false) : ImprovableSearch(improvableSearch) { }

    /// @brief Creates a new Linked List with a Node that represents the its head, (this includes
    /// every Node that the head points to too).
    /// @param head A pointer to the Node that'll be the head of the Linked List.
    /// @param improvableSearch Determines whether or not the Linked List will improve its
    /// searching each time it searches for a Node or a value within.
    explicit LinkedList(Node<T>* head, bool improvableSearch = false)
        : head(head), ImprovableSearch(improvableSearch) { Add(head); }

    /// @brief Creates a new Linked List by copying another Linked List as reference.
    /// @param reference The reference of the Linked List that'll be copied.
    LinkedList(const LinkedList<T> &reference)
    {
        for (Node<T>* currentNode = reference.head;
            currentNode; currentNode = currentNode->next)
        {
            if (!currentNode->isConstructed) { Add(currentNode); continue; }
            Add(currentNode->Data);
        }        
    }

    ~LinkedList()
    {
        for (auto &&constructedNode : constructedNodes)
        {
            delete constructedNode;
            constructedNode = nullptr;
        }
    }

private:
    /// @brief The amount of elements currently stored within the Linked List.
    size_t count = 0;
    /// @brief The Node that represents the first Node in the Linked List.
    Node<T>* head = nullptr;
    /// @brief The Node that represents the last Node in the Linked List.
    Node<T>* tail = nullptr;

    // TODO: Change into a Set.
    /// @brief A List that contains all of the constructed Nodes by this Linked List,
    /// to be released from memory eventually.
    DynamicArray<Node<T>*> constructedNodes;

public:
    /// @brief The amount of elements currently stored within the Linked List.
    /// @return The Nodes count of the Linked List.
    size_t Count() const { return count; }
    /// @brief The Node that represents the first Node in the Linked List.
    /// @return The head Node of the Linked List.
    Node<T>* Head() { return head; }
    /// @brief The Node that represents the last Node in the Linked List.
    /// @return The tail Node of the Linked List.
    Node<T>* Tail() { return tail; }

    /// @brief The Node that represents the first Node in the Linked List.
    /// @return The head Node of the Linked List.
    Node<T>* Head() const { return head; }
    /// @brief The Node that represents the last Node in the Linked List.
    /// @return The tail Node of the Linked List.
    Node<T>* Tail() const { return tail; }
    
    /// @brief Determines whether or not the Linked List will improve its
    /// searching each time it searches for a Node or a value within.
    bool ImprovableSearch = false;

    /// @brief Adds a Node to the end of the Linked List.
    /// @param node A pointer to the Node that'll be added to the Linked List.
    /// @param contiguously Determines whether or not the desired Node will be taken with its chain of Nodes,
    /// or it'll be cut out solely.
    void Add(Node<T>* node, const bool &contiguously = true)
    {
        // TODO: Unique Nodes.
        // if (set.Contains(node)) { return; }

        if (!contiguously) { node->next->previous = node->next = nullptr; }

        for ( ; node; node = node->next, count++)
        {
            if (!count)
            {
                head = tail = node;
                continue;
            }

            if (!node->previous) { node->previous = tail; }
            tail->next = node;
            tail = node;
        }
    }

    /// @brief Constructs a Node from a given value, and adds it to the end of the Linked List.
    /// @param value The value of the Node that'll be constructed and added.
    void Add(T value)
    {
        Node<T>* constructedNode = new Node<T>(value);
        constructedNode->isConstructed = true;
        Add(constructedNode);
        constructedNodes.Add(constructedNode);
    }

    /// @brief Constructs Nodes from a given array of values, and adds them to the end of the Linked List.
    /// @param array The array that consists of values that the Nodes will be constructed from and added.
    void AddRange(const Array<T> &array)
    { for (auto &&value : array) { Add(T(value)); } }

    /// @brief Constructs Nodes from given values, and adds them to the end of the Linked List.
    /// @param length The amount of values that the Nodes will be constructed from and added
    /// to the Linked List.
    /// @param values A pointer to an array in memory, that has some values that'll be used to
    /// construct the Nodes and add them to the Linked List.
    void AddRange(const size_t &length, T* values) { AddRange(Array<T>(length, values)); }

    /// @brief Adds a Node into the Linked List at a specified index.
    /// @param node A pointer to the Node that'll be inserted into the Linked List.
    /// @param index The order in which the desired Node will be inserted at.
    /// @param contiguously Determines whether or not the desired Node will be taken with its chain of Nodes,
    /// or it'll be cut out solely.
    void Insert(Node<T>* node, const size_t &index, const bool &contiguously = true) noexcept(false)
    {
        if (index == count || !index && !count) { Add(node, contiguously); return; }

        ValidateBoundaries(index);

        if (!contiguously) { node->next = nullptr; }
        
        Node<T>
            *atIndexNode = NodeAt(index),
            *preIndexNode = atIndexNode->previous,
            *lastNode = node->Last(),
            *counterNode = node;

        if (preIndexNode) { preIndexNode->next = node; }
        else { head = node; }

        atIndexNode->previous = lastNode ? lastNode: node;
        node->previous = preIndexNode;

        while (counterNode) { count++; counterNode = counterNode->next; }

        if (lastNode) { lastNode->next = atIndexNode; }
        else { node->next = atIndexNode; }
    }

    /// @brief Constructs a Node from a given value, and adds it into the Linked List at a specified index.
    /// @param value The value of the Node that'll be constructed from and inserted into the Linked List.
    /// @param index The order in which the constructed Node will be inserted at.
    void Insert(T value, const size_t &index) noexcept(false)
    {
        if (index == count || !index && !count) { Add(value); return; }

        ValidateBoundaries(index);
        
        Node<T>* constructedNode = new Node<T>(value);
        constructedNodes.Add(constructedNode);
        Insert(constructedNode, index);
    }

    /// @brief Constructs Nodes from a given Array of values, and adds them into the Linked List
    /// at a specified index.
    /// @param array The array that consists of values that the Nodes will be constructed from and added.
    /// @param index The order in which the constructed Nodes will be inserted at.
    void InsertRange(const Array<T> &array, const size_t &index) noexcept(false)
    {
        if (index == count || !index && !count) { AddRange(array); return; }

        ValidateBoundaries(index);
        
        if (!array.Length()) { return; }

        Node<T>* firstConstructedNode = new Node<T>(*array.begin());
        constructedNodes.Add(firstConstructedNode);

        Node<T>* lastConstructedNode = firstConstructedNode;
        for (int i = 1; i < array.Length(); i++)
        {
            Node<T>* constructedNode = new Node<T>(array[i], lastConstructedNode);
            constructedNodes.Add(constructedNode);
            lastConstructedNode = constructedNode;
        }
        Insert(firstConstructedNode, index);
    }
    
    /// @brief Constructs Nodes from given values, and adds them into the Linked List at a specified index.
    /// @param length The amount of values that the Nodes will be constructed from and added
    /// into the Linked List.
    /// @param values A pointer to an array in memory, that has some values that'll be used to
    /// construct the Nodes and add them into the Linked List.
    /// @param index The order in which the constructed Nodes will be inserted at.
    void InsertRange(const size_t &length, T* data, const size_t &index) noexcept(false)
    { InsertRange(Array<T>(length, data), index); }

    /// @brief Gets or Sets a Node in the Linked List, with two ways of indexing.
    /// @param index The order of the desired Node.
    /// @param headToTail Determines whether or not the indexing will start from first to last.
    /// @return A pointer to the Node.
    Node<T>* NodeAt(const size_t &index, const bool &headToTail = true) const noexcept(false)
    {
        ValidateBoundaries(index);

        Node<T>* node = headToTail ? head : tail;

        for (int i = headToTail ? 0 : count - 1;
            headToTail ? i < index : i > index;
            i += headToTail ? +1 : -1)
        { node = headToTail ? node->next : node->previous; }

        return node;
    }

    /// @brief Searches for a Node in the Linked List, and returns its occuring index.
    /// @param node A pointer to the desired Node.
    /// @param headToTail Determines whether or not to search from head to tail.
    /// @return The occuring index of the Node, or -1 if unfound.
    int IndexOf(Node<T>* node, const bool &headToTail = true) const
    {   
        int index = 0;
        for (Node<T>* currentNode = head; currentNode; currentNode = currentNode->next, index++)
        { if (currentNode == node) { return index; } }

        return -1;
    }

    /// @brief Searches for a Node in the Linked List that has a specified value,
    /// and returns the first one to match, then shifts the Node towards the head if allowed to.
    /// @param value The desired value of the Node that'll be searched for.
    /// @return A pointer to the first Node that has the same desired value, or null pointer if unfound.
    Node<T>* FindFirstNode(const T &value) { return FirstNode([&](auto node) { return node->Data == value; }); }

    /// @brief Searches for a Node in the Linked List that has a specified value,
    /// and returns the last one to match, then shifts the Node towards the tail if allowed to.
    /// @param value The desired value of the Node that'll be searched for.
    /// @return A pointer to the last Node that has the same desired value, or null pointer if unfound.
    Node<T>* FindLastNode(const T &value) { return LastNode([&](auto node) { return node->Data == value; }); }

    /// @brief Searches for all the Nodes in the Linked List that have a specified value,
    /// and returns every one that matches, (and doesn't shift Nodes even if allowed to).
    /// @param value The desired value of the Nodes that'll be searched for.
    /// @param headToTail Determines whether or not to search from head to tail.
    /// @return An Array of pointers to all of the Nodes that have the same desired value,
    /// or an empty Array if unfound.
    Array<Node<T>*> FindAllNodes(const T &value, const bool &headToTail = true)
    { return AllNodes([&](Node<T>* node) -> bool { return node->Data == value; }, headToTail); }
    
    /// @brief Searches for a Node in the Linked List that matches a set of conditions,
    /// and returns the first one to match, then shifts the Node towards the head if allowed to.
    /// @param predicate A function that takes a pointer to a Node and validates it
    /// throughout a set of conditions.
    /// @return A pointer to the first Node that has the same desired value, or null pointer if unfound.
    Node<T>* FirstNode(std::function<bool(Node<T>* node)> predicate)
    {
        auto nodes = EveryNode(predicate, true, 1);
        return nodes.Length() ? nodes[0] : nullptr;
    }

    /// @brief Searches for a Node in the Linked List that matches a set of conditions,
    /// and returns the last one to match, then shifts the Node towards the tail if allowed to.
    /// @param predicate A function that takes a pointer to a Node and validates it
    /// throughout a set of conditions.
    /// @return A pointer to the last Node that has the same desired value, or null pointer if unfound.
    Node<T>* LastNode(std::function<bool(Node<T>* node)> predicate)
    {
        auto nodes = EveryNode(predicate, false, 1);
        return nodes.Length() ? nodes[0] : nullptr;
    }

    /// @brief Searches for all the Nodes in the Linked List that match a set of conditions,
    /// and returns every one that matches, (and doesn't shift Nodes even if allowed to).
    /// @param predicate A function that takes a pointer to a Node and validates it
    /// throughout a set of conditions.
    /// @param headToTail Determines whether or not to search from head to tail.
    /// @return An Array of pointers to all of the Nodes that have the same desired value,
    /// or an empty Array if unfound.
    Array<Node<T>*> AllNodes(std::function<bool(Node<T>* node)> predicate, const bool &headToTail = true)
    { return EveryNode(predicate, headToTail); }

    /// @brief Checks for the existence of a Node with a specific value in the Linked List,
    /// (and doesn't shift Nodes even if allowed to).
    /// @param value The value of the desired Node.
    /// @param headToTail Determines whether or not to search from head to tail.
    /// @return A boolean representing whether or not the Node exists within the Linked List.
    bool Contains(const T &value, const bool &headToTail = true)
    {
        bool improvableSearchingState = ImprovableSearch;

        ImprovableSearch = false;
        bool doesNodeExist = (headToTail ? FindFirstNode(value) : FindLastNode(value)) != nullptr;
        ImprovableSearch = improvableSearchingState;

        return doesNodeExist;
    }
    
    /// @brief Removes a Node from the Linked List.
    /// @param node A pointer to the Node that'll be removed.
    void Remove(Node<T> *node, const bool &headToTail = true)
    {
        if (!node) { return; }

        if (node != head) { node->previous->next = node->next; }
        else { head = node->next; }

        if (node != tail) { node->next->previous = node->previous; }
        else { tail = node->previous; }
        
        node->next = node->previous = nullptr;
        count--;
    }

    /// @brief Removes a Node that has a specified value from the Linked List.
    /// @param value The value of the Node that'll be removed.
    /// @param headToTail Determines whether or not to search from head to tail.
    /// @return A boolean representing whether or not the Node has been removed.
    bool Remove(const T &value, const bool &headToTail = true)
    {
        auto node = headToTail ? FindFirstNode(value) : FindLastNode(value);
        if (!node) { return false; }

        Remove(node);
        return true;
    }

    /// @brief Removes all the Nodes that have a specified value from the Linked List.
    /// @param value The value of the Nodes that'll be removed.
    /// @param headToTail Determines whether or not to search from head to tail.
    /// @return A boolean representing whether or not the Nodes have been removed.
    bool RemoveAll(const T &value, const bool &headToTail = true)
    {
        auto nodes = FindAllNodes(value, headToTail);
        if (!nodes.Length()) { return false; }

        for (auto &&node : nodes) { Remove(node); }
        return true;
    }
    
    /// @brief Removes a Node that at a specified index from the Linked List.
    /// @param index The index of the Node that'll will be removed.
    /// @param headToTail Determines whether or not to search from head to tail.
    void RemoveAt(const size_t &index, const bool &headToTail = true) noexcept(false)
    {
        ValidateBoundaries(index);

        auto node = NodeAt(index, headToTail);
        Remove(node);
    }

    /// @brief Removes a range of Nodes from the Linked List starting from a specified index.
    /// @param index The order in which the removal will start from.
    /// @param count The amount of Nodes will be removed.
    /// @param headToTail Determines whether or not to search and remove from head to tail.
    void RemoveRange(const size_t &index, size_t count, const bool &headToTail = true) noexcept(false)
    {
        if (!this->count && !index && !count) { return; }
        
        ValidateBoundaries(index);
        ValidateBoundaries(index + count - 1);

        size_t currentIndex = 0;
        for (auto currentNode = NodeAt(currentIndex + index, headToTail),
                otherNode = currentNode->next;
            currentIndex < count;
            currentNode = otherNode, otherNode = otherNode ? otherNode->next : nullptr, currentIndex++)
        { Remove(currentNode, headToTail); }
    }

    /// @brief Clears every Node from the Linked List.
    void Clear() { RemoveRange(0, count); }

    /// @brief Applies a callback Function for each Node in the Linked List.
    /// @param callback The function that'll be applied to all Nodes, that takes a pointer to the
    /// current Node.
    /// @param headToTail Determines whether or not to callback Function will be applied
    /// from head to tail.
    void Foreach(std::function<void(Node<T>* node)> callback, const bool &headToTail = true)
    { Foreach([&](auto node, auto index) { callback(node); }); }

    /// @brief Applies an indexed callback Function for each Node in the Linked List.
    /// @param callback The function that'll be applied to all Nodes, that takes a pointer to the
    /// current Node, and the index of it.
    /// @param headToTail Determines whether or not to callback Function will be applied
    /// from head to tail.
    void Foreach(std::function<void(Node<T>* node, const size_t &index)> callback, const bool &headToTail = true)
    {
        size_t index = headToTail ? 0 : count - 1;
        for (Node<T>* currentNode = headToTail ? head : tail; currentNode;
            currentNode = headToTail ? currentNode->next : currentNode->previous, index += headToTail ? +1 : -1)
        { callback(currentNode, index); }
    }

    /// @brief Swaps two Nodes linking within the Linked List, and maintain the head and
    /// tail of it, (without affecting the addresses).
    /// @param node1 A pointer to the first Node.
    /// @param node2 A pointer to the second Node.
    void SwapNodes(Node<T>* node1, Node<T>* node2)
    {
        if (!ImprovableSearch)
        { throw std::logic_error("Attempting to adjust the order of a non-improvable-search Linked List."); }

        if (!node1 || !node2) { return; }

        head =
            node1 == head ? node2 :
            node2 == head ? node1 : head;

        tail =
            node1 == tail ? node2 :
            node2 == tail ? node1 : tail;
        
        Node<T>::Swap(node1, node2);
    }
    
    /// @brief Reverses the flow direction of the Nodes within the Linked List.
    void Reverse()
    {
        if (!count) { return; }

        Node<T> *previousNode = nullptr, *currentNode = head, *nextNode = nullptr, *secondNode = head->next;
        while (currentNode)
        {
            nextNode = currentNode->next;
            currentNode->next = previousNode;
            previousNode = currentNode;
            currentNode = nextNode;
        }
        
        std::swap(head, tail);
        head->previous = nullptr;
        tail->previous = secondNode;
    }
    
    /// @brief Removes all the Nodes that have repeated values from the Linked List.
    void Singularize()
    {
        for (Node<T>* node1 = head; node1; node1 = node1->next)
        {
            for (Node<T>* node2 = node1->next; node2; )
            {
                if (node2->Data != node1->Data) { node2 = node2->next; continue; }

                Node<T>* nextNode = node2->next;
                Remove(node2);
                node2 = nextNode;
            }
        }
    }

    /// @brief Converts the Linked List into an Array made out of the Nodes values.
    /// @return An Array consisting of all of the Nodes values of the Linked List.
    Array<T> ToArray() const
    {
        Array<T> array(count);

        size_t index = 0;
        for (Node<T>* currentNode = head; currentNode; currentNode = currentNode->next)
        { array[index++] = currentNode->Data; }

        return array;
    }
    
    /// @brief Converts the Linked List into a List made out of the Nodes values.
    /// @return A List consisting of all of the Nodes values of the Linked List.
    DynamicArray<T> ToList() const { return DynamicArray<T>(ToArray()); }
    
    /// @brief Copies a Linked List into another.
    /// @param reference The reference of the Linked List that'll be copied.
    /// @return The result of the copying.
    LinkedList<T> &operator=(const LinkedList<T> &reference)
    {
        if (this == &reference) { return *this; }

        for (auto &&constructedNode : constructedNodes)
        {
            delete constructedNode;
            constructedNode = nullptr;
        }

        for (Node<T>* currentNode = reference.head;
            currentNode; currentNode = currentNode->next)
        {
            if (!currentNode->isConstructed) { Add(currentNode); continue; }
            Add(currentNode->Data);
        }
        
        return *this;
    }

    /// @brief Adds a Node to the end of the Linked List contiguously.
    /// @param node A pointer to the Node that'll be added to the Linked List.
    /// @return The reference of the Linked List after adding the Node to it.
    LinkedList<T> &operator<<(Node<T>* node) { Add(node); return *this; }
    
    /// @brief Constructs a Node from a given value, and adds it to the end of the Linked List.
    /// @param value The value of the Node that'll be constructed and added.
    /// @return The reference of the Linked List after adding the constructed Node to it.
    LinkedList<T> &operator<<(T value) { Add(value); return *this; }
    
    /// @brief Constructs Nodes from a given array of values, and adds them to the end of the Linked List.
    /// @param array The array that consists of values of the Nodes will be constructed from and added.
    /// @return The reference of the Linked List after adding the constructed Nodes to it.
    LinkedList<T> &operator<<(const Array<T> &array) { AddRange(array); return *this; }

    /// @brief Gets or Sets a Node in the Linked List, (the indexing starts from head to tail).
    /// @param index The order of the desired Node.
    /// @return A pointer to the Node.
    Node<T>* operator[](const size_t &index) const noexcept(false) { return NodeAt(index); }
    
private:
    /// @brief Checks whether or not an index is within the boundaries of the Linked List,
    /// if not, it'll throw an "out of range" exception.
    /// @param index The selected index that'll be checked.
    void ValidateBoundaries(const size_t &index) const noexcept(false)
    {
        if (index < count) { return; }

        throw std::out_of_range("The index [" + std::to_string(index) + "] is out of the range of the Linked List.");
    }
    
    /// @brief Searches for a specified amount of the Nodes in the Linked List that have a specified value,
    /// and returns every one that matches, (and doesn't shift Nodes if asked for more than one even if allowed to).
    /// @param value The desired value of the Nodes that'll be searched for.
    /// @param headToTail Determines whether or not to search from head to tail, and the
    /// shifting towards the head or tail.
    /// @param amountTaken The amount of desired Nodes to be taken and searched for, (will take as much as
    /// possible if given a negative value).
    /// @return An Array of pointers to all of the Nodes that have the same desired value,
    /// or an empty Array if unfound.
    Array<Node<T>*> FindNodes(const T &value, const bool &headToTail, const size_t &amountTaken = 0)
    { return EveryNode([&](auto node) { return node->Data == value; }, headToTail, amountTaken); }
    
    /// @brief Searches for a specified amount of the Nodes in the Linked List that match a set of conditions,
    /// and returns every one that matches, (and doesn't shift Nodes if asked for more than one, even if allowed to).
    /// @param predicate A function that takes a pointer to a Node and validates it
    /// throughout a set of conditions.
    /// @param headToTail Determines whether or not to search from head to tail, and the
    /// shifting towards the head or tail.
    /// @param amountTaken The amount of desired Nodes to be taken and searched for, (will take as much as
    /// possible if assigned to zero).
    /// @return An Array of pointers to all of the Nodes that have the same desired value,
    /// or an empty Array if unfound.
    Array<Node<T>*> EveryNode(std::function<bool(Node<T>* node)> predicate,
        const bool &headToTail, const size_t &amountTaken = 0)
    {
        size_t nodeCount = 0;
        Array<Node<T>*> nodes(!amountTaken ? count : amountTaken);

        for (Node<T>* currentNode = headToTail ? head : tail;
            nodeCount < nodes.Length() && currentNode;
            currentNode = headToTail ? currentNode->next : currentNode->previous)
        {
            if (!predicate(currentNode)) { continue; }

            nodes[nodeCount++] = currentNode;
            
            if (amountTaken && ImprovableSearch)
            { SwapNodes(currentNode, headToTail ? currentNode->previous : currentNode->next); }
        }

        return nodes.Resize(nodeCount);
    }
};

#endif