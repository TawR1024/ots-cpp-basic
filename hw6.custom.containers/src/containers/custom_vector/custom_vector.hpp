#pragma once

#include <iostream>

#include "../../../include/containers/container.hpp"

#define DEFAULT_CAPACITY 10

namespace vector
{

template <typename T>
class custom_vector : public container<T>
{
   private:
    T*     data;
    size_t capacity;
    size_t current_size;
    void   resize ();

   public:
    /// @brief Default constructor, creates vector with DEFAULT_CAPACITY capacity
    custom_vector ();
    /// @brief Constructor with specified initial capacity
    /// @param initial_capacity Initial capacity of the vector (DEFAULT_CAPACITY used if 0)
    custom_vector (size_t initial_capacity);
    /// @brief Copy constructor
    custom_vector (const custom_vector& other);
    /// @brief Copy assignment operator
    custom_vector& operator= (const custom_vector& other);
    /// @brief Move constructor
    custom_vector (custom_vector&& other) noexcept;
    /// @brief Move assignment operator
    custom_vector& operator= (custom_vector&& other) noexcept;
    /// @brief Destructor
    ~custom_vector ();

    // Implement container interface

    /// @brief Adds an element to the end of the vector
    /// @param value The value to add
    void push_back (T value) override;
    /// @brief Removes an element at the specified index
    /// @param index The index of the element to remove
    void erase (size_t index) override;
    /// @brief Inserts an element at the specified index
    /// @param index The index where to insert the element
    /// @param value The value to insert
    void insert (size_t index, T value) override;
    /// @brief Returns the number of elements in the vector
    /// @return The size of the vector
    size_t size () const override { return current_size; };
    /// @brief Checks if the vector is empty
    /// @return true if the vector is empty, false otherwise
    bool empty () const override { return current_size == 0; };
    /// @brief Clears all elements from the vector
    void clear () override
    {
        current_size = 0;
        delete[] data;
        data = new T[capacity];
    };

    /// @brief Accesses the element at the specified index (non-const version)
    /// @param index The index of the element to access
    /// @return Reference to the element at the specified index
    /// @throws std::out_of_range if index is out of bounds
    T& operator[] (size_t index) override
    {
        if (index >= current_size)
        {
            throw std::out_of_range ("Index out of range");
        }
        return data[index];
    }

    /// @brief Accesses the element at the specified index (const version)
    /// @param index The index of the element to access
    /// @return Const reference to the element at the specified index
    /// @throws std::out_of_range if index is out of bounds
    const T& operator[] (size_t index) const
    {
        if (index >= current_size)
        {
            throw std::out_of_range ("Index out of range");
        }
        return data[index];
    }
};

template <typename T>
void custom_vector<T>::resize ()
{
    size_t new_capacity;
    if (capacity < 1024)
    {
        new_capacity = capacity * 2;
    }
    else
    {
        new_capacity = static_cast<size_t> (capacity * 1.25);
        if (new_capacity <= capacity)
        {
            new_capacity = capacity + 1;
        }
    }

    // migrate data to new memory allocation;
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < current_size; ++i)
    {
        new_data[i] = data[i];
    }

    // update old data;
    delete[] data;
    data     = new_data;
    capacity = new_capacity;
}

template <typename T>
custom_vector<T>::custom_vector () : data (nullptr), capacity (DEFAULT_CAPACITY), current_size (0)
{
    // Initialize with default capacity
    data = new T[DEFAULT_CAPACITY];
}

template <typename T>
custom_vector<T>::custom_vector (size_t initial_capacity)
    : data (nullptr), capacity (initial_capacity), current_size (0)
{
    // Initialize with specified capacity
    if (initial_capacity == 0)
    {
        capacity = DEFAULT_CAPACITY;
    }
    data = new T[capacity];
}

template <typename T>
custom_vector<T>::custom_vector (const custom_vector& other)
    : capacity (other.capacity), current_size (other.current_size)
{
    data = new T[capacity];
    for (size_t i = 0; i < current_size; ++i)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
custom_vector<T>::custom_vector (custom_vector&& other) noexcept
    : data (other.data), capacity (other.capacity), current_size (other.current_size)
{
    other.data         = nullptr;
    other.capacity     = 0;
    other.current_size = 0;
}

template <typename T>
custom_vector<T>& custom_vector<T>::operator= (const custom_vector& other)
{
    if (this != &other)
    {
        delete[] data;
        capacity     = other.capacity;
        current_size = other.current_size;
        data         = new T[capacity];
        for (size_t i = 0; i < current_size; ++i)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
custom_vector<T>& custom_vector<T>::operator= (custom_vector&& other) noexcept
{
    if (this != &other)
    {
        delete[] data;
        data               = other.data;
        capacity           = other.capacity;
        current_size       = other.current_size;
        other.data         = nullptr;
        other.capacity     = 0;
        other.current_size = 0;
    }
    return *this;
}

template <typename T>
custom_vector<T>::~custom_vector ()
{
    delete[] data;
}

template <typename T>
void custom_vector<T>::push_back (T value)
{
    if (current_size >= capacity)
    {
        resize ();
    }
    data[current_size++] = value;
}

template <typename T>
void custom_vector<T>::erase (size_t index)
{
    if (index >= current_size)
    {
        throw std::out_of_range ("Index out of range");
    }

    // Shift elements to the left
    for (size_t j = index; j < current_size - 1; ++j)
    {
        data[j] = data[j + 1];
    }
    --current_size;
}

template <typename T>
void custom_vector<T>::insert (size_t index, T value)
{
    if (index > current_size)
    {
        throw std::out_of_range ("Index out of range");
    }

    if (current_size >= capacity)
    {
        resize ();
    }

    // Shift elements to the right starting from the end
    for (size_t i = current_size; i > index; --i)
    {
        data[i] = data[i - 1];
    }

    // Insert new element
    data[index] = value;

    ++current_size;
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const custom_vector<T>& vec)
{
    os << "[ ";
    for (size_t i = 0; i < vec.size (); ++i)
    {
        os << vec[i];
        if (i < vec.size () - 1)
            os << ", ";
    }
    os << " ]";
    return os;
}

}  // namespace vector