#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;
using std::runtime_error;

/**
 * @brief Function pointer type definition
 * C-style "visit" function pointer. It takes a reference to the data and a 'void*' for user-defined context.
 */
template <class T>
using visit_t = void (*)(T& item, void* userData);


/**
 * @brief Represents a node in the Binary Search Tree.
 * @tparam T The data type stored in the node.
 */
template <class T>
struct Node
{
    /// @brief The data value stored in the node.
    T info;
    /// @brief Pointer to the left child node.
    Node<T> *left;
    /// @brief Pointer to the right child node.
    Node<T> *right;
};

/**
 * @brief A templated class implementing a Binary Search Tree (BST).
 * * This class manages the tree structure, providing methods for insertion,
 * deletion, searching, and different traversal orders. It adheres to the
 * Rule of Three by providing a destructor, copy constructor, and
 * copy assignment operator.
 * * @tparam T The type of data elements stored in the BST. This type must support
 * comparison operators (<, >, ==).
 */
template <class T>
class Bst
{
public:
    /**
     * @brief Default constructor.
     * Initializes an empty tree by setting the root pointer to nullptr.
     */
    Bst(): m_root(nullptr) {};

    /**
     * @brief Destructor.
     * Calls DestroyTree() to recursively deallocate all nodes in the tree.
     */
    ~Bst();

    /**
     * @brief Copy constructor for deep copying the BST.
     * @param otherTree The BST object to be copied.
     */
    Bst(const Bst& otherTree); // copy constructor

    /**
     * @brief Copy assignment operator for deep copying the BST.
     * Handles self-assignment and performs a deep copy of the structure.
     * @param other The BST object on the right-hand side of the assignment.
     * @return A constant reference to the current object (*this).
     */
    const Bst& operator=(const Bst&); // copy assignment operator

    /**
     * @brief Checks if the tree is empty.
     * @return true if the root is nullptr, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Deallocates all nodes in the tree.
     * Public wrapper for the private destroy() helper function.
     */
    void DestroyTree();

    // ---
    // MODIFIED TRAVERSAL ROUTINES
    //    Takes a function pointer and user data.
    // ---

    /**
     * @brief Performs an InOrder traversal, calling 'visit_func' on each node.
     * @param visit_func The function pointer to call for each item.
     * @param userData A void pointer to pass 'context' (e.g., a collector object).
     */
    void InOrder(visit_t<T> visit_func, void* userData);

    /**
     * @brief Performs a PreOrder traversal, calling 'visit_func' on each node.
     * @param visit_func The function pointer to call for each item.
     * @param userData A void pointer to pass 'context' (e.g., a collector object).
     */
    void PreOrder(visit_t<T> visit_func, void* userData);

    /**
     * @brief Performs a PostOrder traversal, calling 'visit_func' on each node.
     * @param visit_func The function pointer to call for each item.
     * @param userData A void pointer to pass 'context' (e.g., a collector object).
     */
    void PostOrder(visit_t<T> visit_func, void* userData);

    /**
     * @brief Inserts a new element into the BST while maintaining the search tree property.
     * @param data The element to be inserted.
     */
    void Insert(const T & data);

    /**
     * @brief Searches for a specific element in the tree.
     * @param data The element to search for (used for comparison).
     * @return A non-const pointer to the data in the tree, or nullptr if not found.
     */
    T* Search(const T& data);

    /**
     * @brief Searches for a specific element in the tree (const-safe version).
     * @param data The element to search for (used for comparison).
     * @return A const pointer to the data in the tree, or nullptr if not found.
     */
    const T* Search(const T& data) const;


    /**
     * @brief Deletes a node containing the specified target data.
     * Handles nodes with zero, one, or two children.
     * @param deleteTarget The value of the node to be deleted.
     */
    void DeleteNode(const T& deleteTarget);

private:
    /// @brief Pointer to the root node of the BST.
    Node<T> *m_root;

    /// @brief Recursive helper function to perform a deep copy of the tree structure.
    void copyTree(Node<T>* &copiedTreeRoot, Node<T>* otherTreeRoot);

    /// @brief Recursive helper function to deallocate all nodes in the tree (post-order traversal).
    void destroy(Node<T>* &p);

    // ---
    // PRIVATE TRAVERSAL HELPERS
    // ---
    void inorder(Node<T> *p, visit_t<T> visit_func, void* userData);
    void preorder(Node<T> *p, visit_t<T> visit_func, void* userData);
    void postorder(Node<T> *p, visit_t<T> visit_func, void* userData);

    /// @brief Recursive helper function for inserting a node.
    void insert(Node<T>* &p, const T& data);

    // ---
    // PRIVATE SEARCH HELPERS
    // ---
    T* search(Node<T> *p, const T& data);
    const T* search(Node<T> *p, const T& data) const;

    /// @brief Recursive helper function for deleting a node.
    void deleteNode(Node<T>* &p, const T& deleteTarget);

    /**
     * @brief Finds the minimum value in a given subtree.
     * Used by deleteNode to find the inorder successor (smallest element in the right subtree).
     * @param p The root of the subtree to search.
     * @return The minimum value found.
     * @throw std::runtime_error if called on a nullptr.
     */
    T getMin(Node<T>* p) const;
};

template <class T>
bool Bst<T>::isEmpty() const
{
    return (m_root == nullptr);
}

template <class T>
void Bst<T>::DestroyTree()
{
    destroy(m_root);
}

template <class T>
Bst<T>::~Bst()
{
    DestroyTree();
}

// Private Recursive Helper to destroy the tree
template <class T>
void Bst<T>::destroy(Node<T>* &p)
{
    if (p != nullptr)
    {
        destroy(p->left);
        destroy(p->right);
        delete p;
        p = nullptr;
    }
}

// --- Copy Operations ---

// Private Recursive Helper to perform deep copy
template <class T>
void Bst<T>::copyTree(Node<T>* &copiedTreeRoot, Node<T>* otherTreeRoot)
{
    if (otherTreeRoot == nullptr)
    {
        copiedTreeRoot = nullptr;
    }
    else
    {
        copiedTreeRoot = new Node<T>;
        copiedTreeRoot->info = otherTreeRoot->info;

        copyTree(copiedTreeRoot->left, otherTreeRoot->left);
        copyTree(copiedTreeRoot->right, otherTreeRoot->right);
    }
}

// Copy Constructor
template <class T>
Bst<T>::Bst(const Bst& otherTree):m_root(nullptr)
{
    copyTree(m_root, otherTree.m_root);
}

// Copy Assignment Operator
template <class T>
const Bst<T>& Bst<T>::operator=(const Bst<T>& other)
{
    if (this != &other)
    {
        DestroyTree();
        copyTree(m_root, other.m_root);
    }
    return *this;
}

// --- Insertion ---
template <class T>
void Bst<T>::Insert(const T& data)
{
    insert(m_root, data);
}

template <class T>
void Bst<T>::insert(Node<T>* &p, const T& data)
{
    if (p == nullptr)
    {
        p = new Node<T>;
        p->info = data;
        p->left = nullptr;
        p->right = nullptr;
    }
    else if (data < p->info)
    {
        insert(p->left, data);
    }
    else if (data > p->info)
    {
        insert(p->right, data);
    }
}

template <class T>
T* Bst<T>::Search(const T& data)
{
    return search(m_root, data);
}

template <class T>
T* Bst<T>::search(Node<T> *p, const T& data)
{
    if (p == nullptr)
    {
        return nullptr;
    }
    else if (data == p->info)
    {
        return &(p->info); // Return ADDRESS of data
    }
    else if (data < p->info)
    {
        return search(p->left, data);
    }
    else
    {
        return search(p->right, data);
    }
}

template <class T>
const T* Bst<T>::Search(const T& data) const
{
    return search(m_root, data);
}

template <class T>
const T* Bst<T>::search(Node<T> *p, const T& data) const
{
    if (p == nullptr)
    {
        return nullptr;
    }
    else if (data == p->info)
    {
        return &(p->info); // Return CONST ADDRESS of data
    }
    else if (data < p->info)
    {
        return search(p->left, data);
    }
    else
    {
        return search(p->right, data);
    }
}

template <class T>
void Bst<T>::InOrder(visit_t<T> visit_func, void* userData)
{
    inorder(m_root, visit_func, userData);
}

template <class T>
void Bst<T>::inorder(Node<T> *p, visit_t<T> visit_func, void* userData)
{
    if (p != nullptr)
    {
        inorder(p->left, visit_func, userData);
        visit_func(p->info, userData); // Call the "visit" function
        inorder(p->right, visit_func, userData);
    }
}

template <class T>
void Bst<T>::PreOrder(visit_t<T> visit_func, void* userData)
{
    preorder(m_root, visit_func, userData);
}

template <class T>
void Bst<T>::preorder(Node<T> *p, visit_t<T> visit_func, void* userData)
{
    if (p != nullptr)
    {
        visit_func(p->info, userData); // Call the "visit" function
        preorder(p->left, visit_func, userData);
        preorder(p->right, visit_func, userData);
    }
}

template <class T>
void Bst<T>::PostOrder(visit_t<T> visit_func, void* userData)
{
    postorder(m_root, visit_func, userData);
}

template <class T>
void Bst<T>::postorder(Node<T> *p, visit_t<T> visit_func, void* userData)
{
    if (p != nullptr)
    {
        postorder(p->left, visit_func, userData);
        postorder(p->right, visit_func, userData);
        visit_func(p->info, userData); // Call the "visit" function
    }
}

// --- Deletion ---
template <class T>
T Bst<T>::getMin(Node<T>* p) const
{
    if (p == nullptr)
    {
        throw runtime_error("Attempted to get minimum of a null node.");
    }
    while (p->left != nullptr)
    {
        p = p->left;
    }
    return p->info;
}

template <class T>
void Bst<T>::DeleteNode(const T& deleteTarget)
{
    deleteNode(m_root, deleteTarget);
}

template <class T>
void Bst<T>::deleteNode(Node<T>* &p, const T& deleteTarget)
{
    if (p == nullptr)
    {
        return;
    }
    else if (deleteTarget < p->info)
    {
        deleteNode(p->left, deleteTarget);
    }
    else if (deleteTarget > p->info)
    {
        deleteNode(p->right, deleteTarget);
    }
    else // Found the node to delete
    {
        Node<T> *temp = p;

        if (p->left == nullptr)
        {
            p = p->right;
            delete temp;
        }
        else if (p->right == nullptr)
        {
            p = p->left;
            delete temp;
        }
        else // Two children
        {
            p->info = getMin(p->right);
            deleteNode(p->right, p->info);
        }
    }
}

#endif // BST_H_INCLUDED
