#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cassert>

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
     *
     * Allocates memory for the vector with the specified initial capacity.
     * If initialCapacity is less than 1, it defaults to 1.
     */
    Vector(int initialCapacity);

    /**
     * @brief Default constructor for Vector.
     *
     * Initializes an empty vector with a default capacity of 1.
     */
    Vector();

    /**
     * @brief Destructor for Vector.
     *
     * Deallocates the dynamically allocated memory used by the vector's data array.
     */
    ~Vector();

    /**
     * @brief Copy constructor for Vector.
     *
     * @param myVector The Vector object to copy.
     *
     * Creates a new Vector object as a copy of another Vector object,
     * performing a deep copy of the elements.
     */
    Vector(const Vector& myVector);

    /**
     * @brief Assignment operator for Vector.
     *
     * @param myVector The Vector object to assign from.
     * @return Vector& A reference to the current Vector object after assignment.
     *
     * Assigns the contents of one Vector object to another,
     * handling self-assignment and performing deep copy if necessary.
     */
    Vector& operator=(const Vector& myVector);

    /**
     * @brief Access operator for Vector (non-const version).
     *
     * @param index The index of the element to access.
     * @return T& A reference to the element at the specified index.
     * @throws AssertException if index is out of bounds.
     *
     * Returns a modifiable reference to the element at the given index.
     * Asserts that the index is within the valid range (0 to count-1).
     */
    T& operator[](int index);

    /**
     * @brief Access operator for Vector (const version).
     *
     * @param index The index of the element to access.
     * @return const T& A const reference to the element at the specified index.
     * @throws AssertException if index is out of bounds.
     *
     * Returns a read-only (constant) reference to the element at the given index.
     * Asserts that the index is within the valid range (0 to count-1).
     */
    const T& operator[](int index) const;

    /**
     * @brief Inserts a value at the end of the Vector.
     *
     * @param value The value to insert.
     *
     * Appends a new element with the given value to the end of the vector.
     * Resizes the vector's internal array if necessary to accommodate the new element.
     */
    void insert(const T& value);

    /**
     * @brief Gets the number of elements currently in the Vector.
     *
     * @return int The current element count.
     *
     * Returns the number of elements that have been inserted into the vector.
     * This is not the same as the allocated capacity.
     */
    int getCount() const;

    /**
     * @brief Gets the allocated capacity of the Vector.
     *
     * @return int The current capacity.
     *
     * Returns the total number of elements the vector's internal array can currently hold
     * without needing to resize. This is greater than or equal to the element count.
     */
    int getCapacity() const;

private:
    T* m_vector;     //!< Pointer to the dynamically allocated array of elements.
    int m_capacity;  //!< The current allocated size of the m_vector array.
    int m_count;     //!< The number of elements currently stored in the vector.

    /**
     * @brief Resizes the internal array to double its capacity.
     *
     * Called when the vector is full and a new element is inserted.
     * Creates a new array with double the current capacity, copies existing elements,
     * and updates the vector to use the new array.
     */
    void Resize();
};

template <class T>
Vector<T>::Vector(): m_capacity(1), m_count(0), m_vector(nullptr)
{
    m_vector = new T[m_capacity];
}

template <class T>
Vector<T>::Vector(int initialCapacity): m_capacity(initialCapacity), m_count(0), m_vector(nullptr)
{
    m_vector = new T[m_capacity];
}

template <class T>
Vector<T>::~Vector()
{
    delete[] m_vector;
    m_vector = nullptr;
    m_capacity = 0;
    m_count = 0;
}

template <class T>
Vector<T>::Vector(const Vector& myVector)
{
    m_capacity = myVector.m_capacity;
    m_count = myVector.m_count;
    m_vector = nullptr;
    m_vector = new T[m_capacity];
    for (int i = 0; i < m_count; ++i) {
        m_vector[i] = myVector.m_vector[i];
    }
}

template <class T>
Vector<T>& Vector<T>::operator = (const Vector& myVector)
{
    if (this == &myVector) {
        return *this;
    }

    if (m_capacity != myVector.m_capacity || (m_capacity == 0 && myVector.m_capacity > 0) ) {
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


template <class T>
T& Vector<T>::operator[](int index)
{
    assert(index >= 0 && index < m_count); // Bounds check: index must be valid
    return m_vector[index];
}

template <class T>
const T& Vector<T>::operator[](int index) const
{
    assert(index >= 0 && index < m_count); // Bounds check for const version as well
    return m_vector[index];
}

template <class T>
void Vector<T>::insert(const T& value)
{
    if (m_count == m_capacity) {
        Resize();
    }
    m_vector[m_count++] = value;
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
    if (newCapacity < 1) newCapacity = 1;

    T* newVector = new T[newCapacity];

    for (int i = 0; i < m_count; ++i) {
        newVector[i] = m_vector[i];
    }

    delete[] m_vector;
    m_vector = newVector;
    m_capacity = newCapacity;
}
#endif // VECTOR_H_INCLUDED
