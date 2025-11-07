#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cassert>
#include <stdexcept>

const int INITIAL_CAPACITY = 20;

/**
 * @brief A dynamic array class (vector) template.
 *
 * @tparam T The type of elements to store in the vector.
 *
 * Implements a dynamic array that automatically resizes as elements are added.
 * Provides common vector operations like insertion, element access, and size management.
 */
template <class T>
class Vector
{
public:
    /**
     * @brief Constructor for Vector with initial capacity.
     *
     * @param initialCapacity The initial allocated size for the vector.
     */
    Vector(int initialCapacity);

    /**
     * @brief Default constructor for Vector.
     *
     * Initializes an empty vector with a default capacity of INITIAL_CAPACITY.
     */
    Vector();

    /**
     * @brief Destructor for Vector.
     */
    ~Vector();

    /**
     * @brief Copy constructor for Vector (Deep Copy Method 1).
     *
     * @param myVector The Vector object to copy.
     */
    Vector(const Vector& myVector);

    /**
     * @brief Assignment operator for Vector (Deep Copy Method 2).
     *
     * @param myVector The Vector object to assign from.
     * @return Vector& A reference to the current Vector object after assignment.
     */
    Vector& operator=(const Vector& myVector);

    /**
     * @brief Access operator for Vector (const version - get element).
     *
     * @param index The index of the element to access.
     * @return const T& A const reference to the element at the specified index.
     * @throws std::out_of_range if index is out of bounds.
     */
    const T& operator[](int index) const; // get element

    /**
     * @brief Access operator for Vector (non-const version - modify element).
     *
     * @param index The index of the element to access.
     * @return T& A non-const reference to the element at the specified index.
     * @throws std::out_of_range if index is out of bounds.
     */
    T& operator[](int index); // modify element

    /**
     * @brief Inserts a data at the specified index.
     *
     * @param data The data to insert.
     * @param index The index where it should be inserted (0 to getCount()).
     * @return true if insertion was successful, false otherwise (e.g., invalid index).
     */
    bool Insert(const T& data, int index);

    /**
     * @brief Deletes the element at the specified index.
     *
     * @param index The index of the element to delete (0 to getCount() - 1).
     * @return true if deletion was successful, false otherwise (e.g., invalid index or empty).
     */
    bool Delete(int index);

    /**
     * @brief Gets the number of elements currently in the Vector.
     *
     * @return int The current element count.
     */
    int getCount() const;

    /**
     * @brief Gets the allocated capacity of the Vector.
     *
     * @return int The current capacity.
     */
    int getCapacity() const;

private:
    T* m_vector;      //!< Pointer to the dynamically allocated array of elements.
    int m_capacity;  //!< The current allocated size of the m_vector array.
    int m_count;     //!< The number of elements currently stored in the vector.

    /**
     * @brief Resizes the internal array to double its capacity.
     */
    void Resize();
};

template <class T>
Vector<T>::Vector(): m_capacity(INITIAL_CAPACITY), m_count(0), m_vector(nullptr)
{
    m_vector = new T[m_capacity];
}

template <class T>
Vector<T>::Vector(int initialCapacity)
{
    if (initialCapacity > 0)
    {
        m_capacity = initialCapacity;
    }
    else
    {
        m_capacity = INITIAL_CAPACITY;
    }
    m_vector = new T[m_capacity]; //attempt to get heap memory

    if (m_vector == nullptr)
    {
        m_capacity = 0;
    }
    m_count = 0;
}

template <class T>
Vector<T>::~Vector()
{
    delete[] m_vector;
    m_vector = nullptr;
}

// Deep Copy Method 1: Copy Constructor
template <class T>
Vector<T>::Vector(const Vector& myVector)
{
    m_capacity = myVector.m_capacity;
    m_count = myVector.m_count;
    m_vector = nullptr; // Initialize to nullptr before new
    m_vector = new T[m_capacity];
    for (int i = 0; i < m_count; ++i) {
        m_vector[i] = myVector.m_vector[i];
    }
}

// Deep Copy Method 2: Assignment Operator
template <class T>
Vector<T>& Vector<T>::operator = (const Vector& myVector)
{
    if (this == &myVector) {
        return *this;
    }

    // Check if current capacity is enough; if not, reallocate
    if (m_capacity < myVector.m_count) {
        delete[] m_vector;
        m_capacity = myVector.m_capacity;
        m_vector = new T[m_capacity];
    }

    m_count = myVector.m_count;
    for (int i = 0; i < m_count; ++i) {
        m_vector[i] = myVector.m_vector[i];
    }
    return *this;
}

// Access operator (const version - get element)
template <class T>
const T& Vector<T>::operator[](int index) const
{
    // Changed assert to a throw for better non-debug error handling, but kept the bounds check logic.
    if (index < 0 || index >= m_count) {
        throw std::out_of_range("Vector index out of bounds (const version).");
    }
    return m_vector[index];
}

// Access operator (non-const version - modify element)
template <class T>
T& Vector<T>::operator[](int index)
{
    if (index < 0 || index >= m_count) {
        throw std::out_of_range("Vector index out of bounds (non-const version).");
    }
    return m_vector[index];
}

// Insert at specific index
template <class T>
bool Vector<T>::Insert(const T& data, int index)
{
    // Valid index is 0 <= index <= m_count (allows insertion at the end)
    if (index < 0 || index > m_count)
    {
        return false;
    }

    if (m_count == m_capacity)
    {
        Resize();
    }

    // Shift elements to the right to make space for the new element
    for (int i = m_count; i > index; --i)
    {
        m_vector[i] = m_vector[i - 1];
    }

    m_vector[index] = data;
    m_count++;
    return true;
}

// Delete at specific index (add)
template <class T>
bool Vector<T>::Delete(int index)
{
    // Valid index is 0 <= index < m_count
    if (index < 0 || index >= m_count)
    {
        return false;
    }

    if (m_count == 0)
    {
        return false; // Cannot delete from an empty vector
    }

    // Shift elements to the left to overwrite the deleted element
    for (int i = index; i < m_count - 1; ++i)
    {
        m_vector[i] = m_vector[i + 1];
    }

    m_count--;
    return true;
}


template <class T>
int Vector<T>::getCount() const
{
    return m_count;
}

template <class T>
int Vector<T>::getCapacity() const
{
    return m_capacity;
}

template <class T>
void Vector<T>::Resize()
{
    int newCapacity = m_capacity * 2;
    if (newCapacity < 1) newCapacity = INITIAL_CAPACITY;

    T* newVector = new T[newCapacity];

    for (int i = 0; i < m_count; ++i) {
        newVector[i] = m_vector[i];
    }

    delete[] m_vector;
    m_vector = newVector;
    m_capacity = newCapacity;
}
#endif // VECTOR_H_INCLUDED
