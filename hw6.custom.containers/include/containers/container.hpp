#pragma once

/**
 * @brief Abstract base class for containers
 *
 * This class defines the interface for all containers that must implement
 * basic operations: adding, removing, inserting elements, getting size,
 * checking for emptiness, and clearing.
 *
 * @tparam T Type of stored elements
 */
template <typename T>
class container
{
   public:
    /**
     * @brief Virtual destructor
     */
    virtual ~container () = default;

    /**
     * @brief Adds an element to the end of the container
     * @param value Element to add
     */
    virtual void push_back (T value) = 0;

    /**
     * @brief Inserts an element into the container at specified position
     * @param index Position where to insert the element
     * @param value Element to insert
     */
    virtual void insert (size_t index, T value) = 0;

    /**
     * @brief Removes an element from the container at specified position
     * @param index Position of the element to remove
     * @return Iterator to the element following the removed element
     */
    virtual void erase (size_t index) = 0;

    /**
     * @brief Returns the number of elements in the container
     * @return Size of the container
     */
    virtual size_t size () const = 0;

    /**
     * @brief Accesses the element at specified position
     * @param index Position of the element to access
     * @return Reference to the element at the specified position
     */
    virtual T& operator[] (size_t index) = 0;

    /**
     * @brief Checks if the container is empty
     * @return true if container is empty, false otherwise
     */
    virtual bool empty () const = 0;

    /**
     * @brief Clears the container, removing all elements
     */
    virtual void clear () = 0;
};
