#include <gtest/gtest.h>
#include "containers/custom_list/custom_list.hpp"

TEST(Custom_list_test, InitContainer)
{ 
    list::custom_list<int> list_int;
    
    EXPECT_TRUE(list_int.empty());
    EXPECT_EQ(list_int.size(), 0);
}

TEST(Custom_list_test, PushBack)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);

    EXPECT_EQ(list_int.size(), 3);
    EXPECT_EQ(list_int[0], 1);
    EXPECT_EQ(list_int[1], 2);
    EXPECT_EQ(list_int[2], 3);
}

TEST(Custom_list_test, PushBackMultiple)
{
    list::custom_list<int> list_int;

    for (int i = 0; i < 10; i++) {
        list_int.push_back(i);
    }

    EXPECT_EQ(list_int.size(), 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(list_int[i], i);
    }
}

TEST(Custom_list_test, InsertAtBeginning)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);

    // Insert at beginning
    list_int.insert(0, 0);
    EXPECT_EQ(list_int.size(), 4);
    EXPECT_EQ(list_int[0], 0);
    EXPECT_EQ(list_int[1], 1);
    EXPECT_EQ(list_int[2], 2);
    EXPECT_EQ(list_int[3], 3);
}

TEST(Custom_list_test, InsertAtMiddle)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);

    // Insert at middle
    list_int.insert(1, 10);
    EXPECT_EQ(list_int.size(), 4);
    EXPECT_EQ(list_int[0], 1);
    EXPECT_EQ(list_int[1], 10);
    EXPECT_EQ(list_int[2], 2);
    EXPECT_EQ(list_int[3], 3);
}

TEST(Custom_list_test, InsertAtEnd)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);

    // Insert at end
    list_int.insert(3, 4);
    EXPECT_EQ(list_int.size(), 4);
    EXPECT_EQ(list_int[0], 1);
    EXPECT_EQ(list_int[1], 2);
    EXPECT_EQ(list_int[2], 3);
    EXPECT_EQ(list_int[3], 4);
}

TEST(Custom_list_test, EraseFromBeginning)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);
    list_int.push_back(4);

    // Erase from beginning
    list_int.erase(0);
    EXPECT_EQ(list_int.size(), 3);
    EXPECT_EQ(list_int[0], 2);
    EXPECT_EQ(list_int[1], 3);
    EXPECT_EQ(list_int[2], 4);
}

TEST(Custom_list_test, EraseFromMiddle)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);
    list_int.push_back(4);

    // Erase from middle
    list_int.erase(1);
    EXPECT_EQ(list_int.size(), 3);
    EXPECT_EQ(list_int[0], 1);
    EXPECT_EQ(list_int[1], 3);
    EXPECT_EQ(list_int[2], 4);
}

TEST(Custom_list_test, EraseFromEnd)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);
    list_int.push_back(4);

    // Erase from end
    list_int.erase(3);
    EXPECT_EQ(list_int.size(), 3);
    EXPECT_EQ(list_int[0], 1);
    EXPECT_EQ(list_int[1], 2);
    EXPECT_EQ(list_int[2], 3);
}

TEST(Custom_list_test, Clear)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);

    EXPECT_EQ(list_int.size(), 3);
    EXPECT_FALSE(list_int.empty());

    list_int.clear();

    EXPECT_EQ(list_int.size(), 0);
    EXPECT_TRUE(list_int.empty());
}

TEST(Custom_list_test, OperatorBracket)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);

    // Check access by valid indices
    EXPECT_EQ(list_int[0], 1);
    EXPECT_EQ(list_int[1], 2);
    EXPECT_EQ(list_int[2], 3);

    // Check access by invalid indices
    EXPECT_THROW(list_int[3], std::out_of_range);
    EXPECT_THROW(list_int[-1], std::out_of_range);
}

TEST(Custom_list_test, CopyConstructor)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);

    // Create copy
    list::custom_list<int> list_copy(list_int);

    // Check that copy contains the same elements
    EXPECT_EQ(list_copy.size(), 3);
    EXPECT_EQ(list_copy[0], 1);
    EXPECT_EQ(list_copy[1], 2);
    EXPECT_EQ(list_copy[2], 3);

    // Check that copy is independent from original
    list_int.push_back(4);
    EXPECT_EQ(list_int.size(), 4);
    EXPECT_EQ(list_copy.size(), 3);
    EXPECT_EQ(list_copy[0], 1);
    EXPECT_EQ(list_copy[1], 2);
    EXPECT_EQ(list_copy[2], 3);
}

TEST(Custom_list_test, CopyAssignment)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);

    list::custom_list<int> list_copy;

    // Assignment
    list_copy = list_int;

    // Check that copy contains the same elements
    EXPECT_EQ(list_copy.size(), 3);
    EXPECT_EQ(list_copy[0], 1);
    EXPECT_EQ(list_copy[1], 2);
    EXPECT_EQ(list_copy[2], 3);

    // Check that copy is independent from original
    list_int.push_back(4);
    EXPECT_EQ(list_int.size(), 4);
    EXPECT_EQ(list_copy.size(), 3);
    EXPECT_EQ(list_copy[0], 1);
    EXPECT_EQ(list_copy[1], 2);
    EXPECT_EQ(list_copy[2], 3);
}

TEST(Custom_list_test, MoveConstructor)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);

    // Create by move
    list::custom_list<int> list_move(std::move(list_int));

    // Check that moved vector contains the same elements
    EXPECT_EQ(list_move.size(), 3);
    EXPECT_EQ(list_move[0], 1);
    EXPECT_EQ(list_move[1], 2);
    EXPECT_EQ(list_move[2], 3);

    // Check that original vector is empty
    EXPECT_EQ(list_int.size(), 0);
    EXPECT_TRUE(list_int.empty());
}

TEST(Custom_list_test, MoveAssignment)
{
    list::custom_list<int> list_int;

    list_int.push_back(1);
    list_int.push_back(2);
    list_int.push_back(3);

    list::custom_list<int> list_move;

    // Assignment by move
    list_move = std::move(list_int);

    // Check that moved vector contains the same elements
    EXPECT_EQ(list_move.size(), 3);
    EXPECT_EQ(list_move[0], 1);
    EXPECT_EQ(list_move[1], 2);
    EXPECT_EQ(list_move[2], 3);

    // Check that original vector is empty
    EXPECT_EQ(list_int.size(), 0);
    EXPECT_TRUE(list_int.empty());
}