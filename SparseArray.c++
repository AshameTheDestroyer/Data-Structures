#include<iostream>

#include "SparseNode.c++"
#include "LinkedList.c++"

#ifndef SPARSE_ARRAY
#define SPARSE_ARRAY

/// @brief A data structure to save incontiguous sparse data in memory.
/// @tparam T The type of the data stored within the Sparse Array.
template<typename T>
class SparseArray
{
public:
    /// @brief Creates a new empty Sparse Array.
    SparseArray() = default;

    /// @brief Creates a new Sparse Array with a defined length, and all elements are set to
    /// their default value.
    /// @param length The amount of elements that'll be stored within the Sparse Array.
    explicit SparseArray(const size_t &length) : length(length) { }

    /// @brief Creates a new Sparse Array with a defined length, and all elements are set to
    /// an initial value.
    /// @param length The amount of elements that'll be stored within the Sparse Array.
    /// @param defaultValue The value that'll be set to each element as a default one.
    SparseArray(const size_t &length, const T &defaultValue) : SparseArray(length) { std::cout<< (DefaultValue = defaultValue) << "\n"; }

    /// @brief Creates a new Sparse Array by copying another Sparse Array as reference.
    /// @param reference The reference of the Sparse Array that'll be copied.
    SparseArray(const SparseArray<T> &reference)
    {
        length = reference.length;
        actualLength = reference.actualLength;

        sparseNodes = LinkedList<SparseNode<T>>();
        for (Node<SparseNode<T>>* currentNode = reference.sparseNodes.Head();
            currentNode; currentNode = currentNode->Next())
        { sparseNodes.Add(currentNode->Data); }
    }

    ~SparseArray() = default;

private:
    /// @brief The amount of elements stored within the Sparse Array.
    size_t length = 0;
    /// @brief The amount of non-default elements stored within the Sparse Array.
    size_t actualLength = 0;

    // TODO: Implement Binary Search.
    /// @brief A Linked List that contains all of the Sparse Nodes created within the Sparse Array.
    LinkedList<SparseNode<T>> sparseNodes;
    
public:
    /// @brief The value that'll be set to each element with an unspecified value.
    T DefaultValue = T();

    /// @brief The amount of elements stored within the Sparse Array.
    /// @return The length of the Sparse Array.
    size_t Length() const { return length; }
    /// @brief The amount of non-default elements stored within the Sparse Array.
    /// @return The actual length of the Sparse Array.
    size_t ActualLength() const { return actualLength; }

    /// @brief Sets an element value within the Sparse Array at a specified index.
    /// @param element The new value of the element that'll be set.
    /// @param index The order in which the desired element will be chosen to set its value.
    SparseArray<T> &Set(const T &element, const size_t &index) noexcept(false)
    {
        ValidateBoundaries(index);
        
        SparseNode<T> sparseNode(element, index);
        if (!actualLength) { sparseNodes.Add(sparseNode); actualLength++; return *this; }

        if (!index)
        {
            if (!sparseNodes.Head()->Data.Index) { sparseNodes.Head()->Data = sparseNode; return *this; }
            sparseNodes.Insert(sparseNode, 0);
            return *this;
        }

        bool inserted = false;
        size_t currentIndex = 0;
        for (Node<SparseNode<T>>* currentNode = sparseNodes.Head();
            currentNode; currentNode = currentNode->Next(), currentIndex++)
        {
            if (currentNode->Data == sparseNode)
            { currentNode->Data = sparseNode; inserted |= true; break; }

            if (currentNode->Data < sparseNode) { continue; }

            sparseNodes.Insert(sparseNode, currentIndex);
            inserted |= true;
        }

        if (!inserted) { sparseNodes.Add(sparseNode); }

        actualLength++;
        return *this;
    }

    void Print() const
    {
        std::cout << " ";
        size_t index = 0;
        for (Node<SparseNode<T>>* currentNode = sparseNodes.Head();
            index < length; currentNode = currentNode ? currentNode->Next() : nullptr, index++)
        {
            bool isCurrentNodeFar = currentNode && index < currentNode->Data.Index,
                isOuttaNodes = !currentNode && index < length;
                
            while (isCurrentNodeFar || isOuttaNodes)
            {
                std::cout << DefaultValue << " ";

                if (isCurrentNodeFar) { isCurrentNodeFar &= ++index < currentNode->Data.Index; }
                if (isOuttaNodes) { isOuttaNodes &= ++index < length; }
            }

            if (currentNode) { std::cout << currentNode->Data << " "; }
        }
        std::cout << "\n";
    }

    /// @brief Copies a Sparse Array into another.
    /// @param reference The reference of the Sparse Array that'll be copied.
    /// @return The result of the copying.
    SparseArray<T> &operator=(const SparseArray<T> &reference)
    {
        if (this == &reference) { return *this; }

        length = reference.length;
        actualLength = reference.actualLength;
        
        sparseNodes = LinkedList<SparseNode<T>>();
        for (Node<SparseNode<T>>* currentNode = reference.sparseNodes.Head();
            currentNode; currentNode = currentNode->Next())
        { sparseNodes.Add(currentNode->Data); }
        
        return *this;
    }
    
    template<typename T_>
    friend std::ostream &operator<<(std::ostream &cout, const SparseArray<T_> &sparseArray);

private:
    /// @brief Checks whether or not an index is within the boundaries of the Sparse Array, if not,
    /// it'll throw an "out of range" exception.
    /// @param index The selected index that'll be checked.
    void ValidateBoundaries(const size_t &index) const noexcept(false)
    {
        if (index < length) { return; }

        throw std::out_of_range("The index [" + std::to_string(index) + "] is out of the range of the Sparse Array.");
    }
};

template<typename T>
static std::ostream &operator<<(std::ostream &cout, const SparseArray<T> &sparseArray) noexcept(false)
{ sparseArray.Print(); return cout; }

/// @brief Simple shortcut of writing Two-Dimensional Sparse Array types.
/// @tparam T The type of the data stored within the Matrix.
template<typename T>
using SparseMatrix = SparseArray<SparseArray<T>>;

/// @brief Simple shortcut of writing Three-Dimensional Sparse Array types.
/// @tparam T The type of the data stored within the Tensor.
template<typename T>
using SparseTensor = SparseArray<SparseArray<SparseArray<T>>>;


#endif