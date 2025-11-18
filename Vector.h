#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cassert>
#include <stdexcept>

const int INITIAL_CAPACITY = 20;

template <class T>
class Vector
{
public:
    /**
     * @brief Constructor for Vector with initial capacity.
     */
    Vector(int initialCapacity);

    /**
     * @brief Default constructor for Vector.
     * FIXED: Initializer list now matches declaration order.
     */
    Vector()
        : m_vector(new T[INITIAL_CAPACITY]),
          m_capacity(INITIAL_CAPACITY),
          m_count(0)
    {
        // Body is now empty
    }

    /**
     * @brief Destructor for Vector.
     */
    ~Vector();

    /**
     * @brief Copy constructor for Vector (Deep Copy Method 1).
     * FIXED: Uses member initializer list and corrects copy bug.
     */
    Vector(const Vector& myVector)
        : m_vector(new T[myVector.m_capacity]),
          m_capacity(myVector.m_capacity),
          m_count(myVector.m_count)
    {
        for (int i = 0; i < m_count; ++i) {
            m_vector[i] = myVector.m_vector[i]; // Corrected copy
        }
    }

    /**
     * @brief Assignment operator for Vector (Deep Copy Method 2).
     */
    Vector& operator=(const Vector& myVector);

    /**
     * @brief Access operator for Vector (const version - get element).
     */
    const T& operator[](int index) const; // get element

    /**
     * @brief Access operator for Vector (non-const version - modify element).
     */
    T& operator[](int index); // modify element

    /**
     * @brief Inserts a data at the specified index.
     */
    bool Insert(const T& data, int index);

    /**
     * @brief Deletes the element at the specified index.
     */
    bool Delete(int index);

    /**
     * @brief Gets the number of elements currently in the Vector.
     */
    int getCount() const;

    /**
     * @brief Gets the allocated capacity of the Vector.
     */
    int getCapacity() const;

private:
    // ---
    // This is the declaration order the compiler uses:
    // 1. m_vector
    // 2. m_capacity
    // 3. m_count
    // ---
    T* m_vector;      //!< Pointer to the dynamically allocated array of elements.
    int m_capacity;  //!< The current allocated size of the m_vector array.
    int m_count;     //!< The number of elements currently stored in the vector.

    /**
     * @brief Resizes the internal array to double its capacity.
     */
    void Resize();
};

// --- (Rest of the file is unchanged) ---

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

    // FIXED: Match declaration order in list
    m_vector = new T[m_capacity];
    m_count = 0;

    if (m_vector == nullptr)
    {
        m_capacity = 0;
    }
}

template <class T>
Vector<T>::~Vector()
{
    delete[] m_vector;
    m_vector = nullptr;
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
    if (index < 0 || index > m_count)
    {
        return false;
    }

    if (m_count == m_capacity)
    {
        Resize();
    }

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
    if (index < 0 || index >= m_count)
    {
        return false;
    }

    if (m_count == 0)
    {
        return false;
    }

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
