#pragma once
#include <iostream>

#include "../../../include/containers/container.hpp"
#include "data_node.hpp"

namespace list
{
/**
 * @brief A custom doubly linked list implementation that inherits from container<T>
 * @tparam T The type of elements stored in the list
 */
template <typename T>
class custom_list : public container<T>
{
   private:
    data_node<T>* head;          ///< Pointer to the first node in the list
    data_node<T>* tail;          ///< Pointer to the last node in the list
    size_t        current_size;  ///< Current number of elements in the list

   public:
    /**
     * @brief Default constructor - creates an empty list
     */
    custom_list ();

    /**
     * @brief Destructor - clears all elements from the list
     */
    ~custom_list ()
    {
        if (head != nullptr || tail != nullptr || current_size != 0)
        {
            clear ();
        }
    };

    /**
     * @brief Adds an element to the end of the list
     * @param value The value to add
     */
    void push_back (T value) override;

    /**
     * @brief Inserts an element at the specified position
     * @param index The position where to insert the element (0-based)
     * @param value The value to insert
     */
    void insert (size_t index, T value) override;

    /**
     * @brief Removes an element at the specified position
     * @param index The position of the element to remove (0-based)
     */
    void erase (size_t index) override;

    /**
     * @brief Returns the number of elements in the list
     * @return The size of the list
     */
    size_t size () const override { return current_size; };

    /**
     * @brief Accesses an element at the specified position (non-const version)
     * @param index The position of the element (0-based)
     * @return Reference to the element at the specified position
     */
    T& operator[] (size_t index) override;

    /**
     * @brief Accesses an element at the specified position (const version)
     * @param index The position of the element (0-based)
     * @return Const reference to the element at the specified position
     */
    const T& operator[] (size_t index) const;

    /**
     * @brief Checks if the list is empty
     * @return true if the list is empty, false otherwise
     */
    bool empty () const override { return current_size == 0; };

    /**
     * @brief Removes all elements from the list
     */
    void clear () override;

    /**
     * @brief Assignment operator - copies elements from another list
     * @param other The list to copy from
     * @return Reference to this list
     */
    custom_list& operator= (const custom_list& other);

    /**
     * @brief Copy constructor - creates a new list by copying elements from another list
     * @param other The list to copy from
     */
    custom_list (const custom_list& other);

    // friend std::ostream& operator<< (std::ostream& os, const custom_list<T>& list);
};

/**
 * @brief Default constructor implementation
 * @tparam T The type of elements stored in the list
 */
template <typename T>
custom_list<T>::custom_list () : head (nullptr), tail (nullptr), current_size (0)
{
}

/**
 * @brief Copy constructor implementation
 * @tparam T The type of elements stored in the list
 * @param other The list to copy from
 */
template <typename T>
custom_list<T>::custom_list (const custom_list<T>& other) : head (nullptr), tail (nullptr), current_size (0)
{
    data_node<T>* current = other.head;
    while (current)
    {
        push_back (current->data);
        current = current->next;
    }
}

/**
 * @brief Clears all elements from the list
 * @tparam T The type of elements stored in the list
 */
template <typename T>
void custom_list<T>::clear ()
{
    if (head == nullptr)
    {
        tail         = nullptr;
        current_size = 0;
        return;
    }

    while (head)
    {
        data_node<T>* temp = head;
        head               = head->next;
        delete temp;
    }
    tail         = nullptr;
    current_size = 0;
}

/**
 * @brief Adds an element to the end of the list
 * @tparam T The type of elements stored in the list
 * @param value The value to add
 */
template <typename T>
void custom_list<T>::push_back (T value)
{
    data_node<T>* new_node = new data_node<T> (value);

    if (head == nullptr)
    {
        head = new_node;
        tail = new_node;
    }
    else
    {
        tail->next     = new_node;
        new_node->prev = tail;
        tail           = new_node;
    }
    current_size++;
}

/**
 * @brief Overloaded output stream operator for custom_list
 * @tparam T The type of elements stored in the list
 * @param os The output stream
 * @param list The list to output
 * @return Reference to the output stream
 */
template <typename T>
std::ostream& operator<< (std::ostream& os, const custom_list<T>& list)
{
    if (list.empty ())
    {
        os << "[ ]";
        return os;
    }

    os << "[ ";
    // data_node<T>* current = list.head;
    // while (current) // TODO: fix this implementatin.
    // {
    //     os << current->data;
    //     if (current->next)
    //     {
    //         os << ", ";
    //     }
    //     current = current->next;
    // }
    for (size_t i = 0; i < list.size (); ++i)
    {
        os << list[i];
        if (i < list.size () - 1)
        {
            os << ", ";
        }
    }
    os << " ]";

    return os;
}

/**
 * @brief Inserts an element at the specified position
 * @tparam T The type of elements stored in the list
 * @param index The position where to insert the element (0-based)
 * @param value The value to insert
 */
template <typename T>
void custom_list<T>::insert (size_t index, T value)
{
    if (index > current_size)
    {
        return;
    }

    if (index == current_size)
    {
        push_back (value);
        return;
    }

    data_node<T>* new_node = new data_node<T> (value);
    data_node<T>* current  = head;

    for (size_t i = 0; i < index; ++i)
    {
        current = current->next;
    }

    new_node->next = current;
    new_node->prev = current->prev;

    if (current->prev)
    {
        current->prev->next = new_node;
    }
    else
    {
        head = new_node;
    }

    current->prev = new_node;
    current_size++;
}

/**
 * @brief Removes an element at the specified position
 * @tparam T The type of elements stored in the list
 * @param index The position of the element to remove (0-based)
 * @throws std::out_of_range if index is out of range
 */
template <typename T>
void custom_list<T>::erase (size_t index)
{
    if (index >= current_size)
    {
        throw std::out_of_range ("index out of range");
    }

    data_node<T>* current = head;
    for (size_t i = 0; i < index; ++i)
    {
        current = current->next;
    }

    if (current->prev)
    {
        current->prev->next = current->next;
    }
    else
    {
        head = current->next;
    }

    if (current->next)
    {
        current->next->prev = current->prev;
    }
    else
    {
        tail = current->prev;
    }

    delete current;
    current_size--;
}

/**
 * @brief Accesses an element at the specified position (non-const version)
 * @tparam T The type of elements stored in the list
 * @param index The position of the element (0-based)
 * @return Reference to the element at the specified position
 * @throws std::out_of_range if index is out of range or list is empty
 */
template <typename T>
T& custom_list<T>::operator[] (size_t index)
{
    if (current_size == 0)
    {
        throw std::out_of_range ("List is empty");
    }

    if (index >= current_size)
    {
        throw std::out_of_range ("Index out of range");
    }

    data_node<T>* current = head;

    for (size_t i = 0; i < index; ++i)
    {
        if (current == nullptr)
        {
            throw std::out_of_range ("Invalid list state - current is nullptr");
        }

        current = current->next;
    }

    if (current == nullptr)
    {
        throw std::out_of_range ("Invalid list state - current is nullptr after loop");
    }

    if (current->next == nullptr && index < current_size - 1)
    {
        throw std::out_of_range ("Inconsistent list state");
    }

    return current->data;
}

/**
 * @brief Accesses an element at the specified position (const version)
 * @tparam T The type of elements stored in the list
 * @param index The position of the element (0-based)
 * @return Const reference to the element at the specified position
 * @throws std::out_of_range if index is out of range or list is empty
 */
template <typename T>
const T& custom_list<T>::operator[] (size_t index) const
{
    if (current_size == 0)
    {
        throw std::out_of_range ("List is empty");
    }

    if (index >= current_size)
    {
        throw std::out_of_range ("Index out of range");
    }

    data_node<T>* current = head;

    for (size_t i = 0; i < index; ++i)
    {
        if (current == nullptr)
        {
            throw std::out_of_range ("Invalid list state - current is nullptr");
        }

        current = current->next;
    }

    if (current == nullptr)
    {
        throw std::out_of_range ("Invalid list state - current is nullptr after loop");
    }

    if (current->next == nullptr && index < current_size - 1)
    {
        throw std::out_of_range ("Inconsistent list state");
    }

    return current->data;
}

/**
 * @brief Assignment operator implementation
 * @tparam T The type of elements stored in the list
 * @param other The list to copy from
 * @return Reference to this list
 */
template <typename T>
custom_list<T>& custom_list<T>::operator= (const custom_list<T>& other)
{
    if (this != &other)
    {
        clear ();
        data_node<T>* current = other.head;
        while (current)
        {
            push_back (current->data);
            current = current->next;
        }
    }
    return *this;
}

}  // namespace list