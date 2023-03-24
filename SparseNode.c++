#include<iostream>

#ifndef SPARSE_NODE
#define SPARSE_NODE

/// @brief A block of code that contains a certain amount of data, and an index of it, to be used
/// in a Sparse Array later on.
/// @tparam T The type of the data stored within the Sparse Node.
template <typename T>
class SparseNode
{
public:
    /// @brief Creates a new empty Sparse Node.
    SparseNode() = default;

    /// @brief Creates a new Sparse Node with a defined data.
    /// @param data The data that'll be stored within the Node.
    /// @param index The index in which the Sparse Node is at in a Sparse Array.
    SparseNode(const T &data, const size_t &index) : Data(data), Index(index) { }

    ~SparseNode() = default;

public:
    /// @brief The data stored within the Sparse Node.
    T Data = T();
    /// @brief The index in which the Sparse Node is at in a Sparse Array.
    size_t Index = 0;

    /// @brief Compares this Sparse Node with another Sparse Node to check if its index is equal to.
    /// @param sparseNode The Sparse Node that'll be compared to.
    /// @return A boolean representing whether or not the index of this Sparse Node is
    /// equal to the other index.
    bool operator==(SparseNode<T> &sparseNode) { return Compare(*this, sparseNode) == 0; }

    /// @brief Compares this Sparse Node with another Sparse Node to check if its index is not equal to.
    /// @param sparseNode The Sparse Node that'll be compared to.
    /// @return A boolean representing whether or not the index of this Sparse Node is
    /// not equal to the other index.
    bool operator!=(SparseNode<T> &sparseNode) { return Compare(*this, sparseNode) != 0; }

    /// @brief Compares this Sparse Node with another Sparse Node to check if its index is smaller.
    /// @param sparseNode The Sparse Node that'll be compared to.
    /// @return A boolean representing whether or not the index of this Sparse Node is
    /// smaller than the other index.
    bool operator<(SparseNode<T> &sparseNode) { return Compare(*this, sparseNode) == -1; }

    /// @brief Compares this Sparse Node with another Sparse Node to check if its index is smaller or equal to.
    /// @param sparseNode The Sparse Node that'll be compared to.
    /// @return A boolean representing whether or not the index of this Sparse Node is
    /// smaller than or equal to the other index.
    bool operator<=(SparseNode<T> &sparseNode) { return Compare(*this, sparseNode) != +1; }

    /// @brief Compares this Sparse Node with another Sparse Node to check if its index is greater.
    /// @param sparseNode The Sparse Node that'll be compared to.
    /// @return A boolean representing whether or not the index of this Sparse Node is
    /// greater than the other index.
    bool operator>(SparseNode<T> &sparseNode) { return Compare(*this, sparseNode) == +1; }

    /// @brief Compares this Sparse Node with another Sparse Node to check if its index is greater or equal to.
    /// @param sparseNode The Sparse Node that'll be compared to.
    /// @return A boolean representing whether or not the index of this Sparse Node is
    /// greater than or equal to the other index.
    bool operator>=(SparseNode<T> &sparseNode) { return Compare(*this, sparseNode) != -1; }
    
    /// @brief Makes the Output Stream extraction operator a friend with the Sparse Node class,
    /// so it can be printed out to the stream.
    /// @tparam T_ The type of the data stored within the Sparse Node.
    /// @param cout The Output Stream that'll print the Sparse Node data out.
    /// @param sparseNode The Sparse Node that will be printed out to the stream.
    /// @return The Output Stream itself after printing the Sparse Node data out.
    template<typename T_>
    friend std::ostream &operator<<(std::ostream &cout, const SparseNode<T_> &sparseNode);
    
    /// @brief Compares two Sparse Nodes indices and return a value that indicates of the result.
    /// @param sparseNode1 The first Sparse Node.
    /// @param sparseNode2 The second Sparse Node.
    /// @return A numeric value indicating the result of the comparison, that is: +1 if the first is greater,
    /// -1 if smaller, and 0 if both are equal.
    static short Compare(SparseNode<T> &sparseNode1, const SparseNode<T> &sparseNode2)
    {
        return
            sparseNode1.Index > sparseNode2.Index ? +1 :
            sparseNode1.Index < sparseNode2.Index ? -1 : 0;
    }
};

/// @brief Prints out a Sparse Node data into an Output Stream.
/// @tparam T The type of the data stored within the Sparse Node.
/// @param cout The Output Stream that'll print the Sparse Node data out.
/// @param sparseNode The Sparse Node that its data will be printed out to the stream.
/// @return The Output Stream itself after printing the Sparse Node data out.
template<typename T>
static std::ostream &operator<<(std::ostream &cout, const SparseNode<T> &sparseNode) noexcept(false)
{ return cout << sparseNode.Data; }

#endif