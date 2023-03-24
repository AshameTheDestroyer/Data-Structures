#include<iostream>

#ifndef NODE
#define NODE

/// @brief Introduces the abstraction of the Linked List class to the Node class.
/// @tparam T The type of the data stored within the Linked List.
template<typename T>
class LinkedList;

/// @brief A block of code that contains a certain amount of data, and points to another block.
/// @tparam T The type of the data stored within the Node.
template<typename T>
class Node
{
public:
    /// @brief Makes the Linked List class a friend with the Node class.
    friend class LinkedList<T>;

    /// @brief Creates a new empty Node.
    Node() = default;

    /// @brief Creates a new Node with a defined data.
    /// @param data The data that'll be stored within the Node.
    Node(const T &data) : Data(data) { }

    /// @brief Creates a new Node with a defined data, and the Node that should point to this Node.
    /// @param data The data that'll be stored within the Node.
    /// @param next A pointer to Node that'll point to this Node as a next Node.
    Node(const T &data, Node* previous) : Data(data), previous(previous) { previous->next = this; }

    ~Node() = default;

private:
    /// @brief The Node that points to this Node as a next Node.
    Node* previous = nullptr;
    /// @brief The Node that this Node points to as a next Node.
    Node* next = nullptr;
    /// @brief Indicates whether or not the Node has been constructed by some Linked List.
    bool isConstructed = false;

public:
    /// @brief The data stored within the Node.
    T Data = T();
    
    /// @brief The Node that points to this Node as a next Node.
    /// @return The previous Node of the Node.
    Node* Previous() { return previous; }
    /// @brief The Node that this Node points to as a next Node.
    /// @return The next Node of the Node.
    Node* Next() { return next; }

    /// @brief The first Node points to this Node.
    /// @return The first Node in this Node chain, excluding this one.
    Node* First()
    {
        Node<T>* node = previous;
        while (node && node->previous) { node = node->previous; }
        return node;
    }

    /// @brief The last Node this Node points to.
    /// @return The last Node in this Node chain, excluding this one.
    Node* Last()
    {
        Node<T>* node = next;
        while (node && node->next) { node = node->next; }
        return node;
    }
    
    /// @brief The first Node points to this Node, or this Node if none.
    /// @return The first Node to this Node chain, including this one.
    Node* FirstInChain() { return previous ? First() : this; }

    /// @brief The last Node points to this Node, or this Node if none.
    /// @return The last Node to this Node chain, including this one.
    Node* LastInChain() { return next ? Last() : this; }

    /// @brief Indicates whether or not this Node has no Node to point to, or pointed to by another Node.
    /// @return A boolean representing whether or not this Node is a singleton Node.
    bool IsSingleton() const { return !previous && !next; }
    
    /// @brief Converts this Node into a singleton Node, by de-linking its chain Nodes.
    void Singularize()
    {
        if (next) { next = next->previous = nullptr; }
        if (previous) { previous = previous->next = nullptr; }
    }

    /// @brief Links a Node to this Node as the next Node.
    /// @param node A pointer to the Node that'll be linked to this Node.
    /// @return A pointer to the Node that has been linked to.
    Node<T> &Link(Node<T>* node)
    {
        next = node;
        node->previous = this;
        return *node;
    }

    /// @brief Makes the Output Stream extraction operator a friend with the Node class,
    /// so it can be printed out to the stream.
    /// @tparam T_ The type of the data stored within the Node.
    /// @param cout The Output Stream that'll print the Node data out.
    /// @param node The Node that its data will be printed out to the stream.
    /// @return The Output Stream itself after printing the Node data out.
    template<typename T_>
    friend std::ostream &operator<<(std::ostream &cout, const Node<T_> &node);

    /// @brief Links a Node to this Node as the next Node.
    /// @param node A pointer to the Node that'll be linked to this Node.
    /// @return A pointer to the Node that has been linked to.
    Node<T> &operator>>(Node<T>* node) { return Link(node); }

    /// @brief Swaps two Nodes linking, (without affecting the addresses).
    /// @param node1 A pointer to the first Node.
    /// @param node2 A pointer to the second Node.
    static void Swap(Node<T>* node1, Node<T>* node2)
    {
        Node<T>
            *previousNode1 = node1->previous,
            *nextNode1 = node1->next,
            *previousNode2 = node2->previous,
            *nextNode2 = node2->next;
        
        PREVIOUS:
        {
            if (previousNode1) { previousNode1->next = node2; }
            if (previousNode2) { previousNode2->next = node1; }
        }

        CURRENT:
        {
            auto temporaryPrevious = node1->previous;
            node1->previous = node2->previous != node1 ? node2->previous : node2;
            node2->previous = temporaryPrevious != node2 ? temporaryPrevious : node1;

            auto temporaryNext = node1->next;
            node1->next = node2->next;
            node2->next = temporaryNext;
        }
        
        NEXT:
        {
            if (nextNode1 && nextNode1 != node2) { nextNode1->previous = node2; }
            if (nextNode2 && nextNode2 != node1) { nextNode2->previous = node1; }
        }
    }
};

/// @brief Prints out a Node data into an Output Stream.
/// @tparam T The type of the data stored within the Node.
/// @param cout The Output Stream that'll print the Node data out.
/// @param node The Node that its data will be printed out to the stream.
/// @return The Output Stream itself after printing the Node data out.
template<typename T>
static std::ostream &operator<<(std::ostream &cout, const Node<T> &node) noexcept(false)
{ return cout << node.Data; }

#endif