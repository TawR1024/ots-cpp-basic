#include "containers/custom_vector/custom_vector.hpp"

#include <gtest/gtest.h>

class Custom_vector_test : public ::testing::Test
{
   protected:
    vector::custom_vector<int> vec_int;
    void                       SetUp () override {}
};

TEST_F (Custom_vector_test, InitContainer)
{
    EXPECT_TRUE (vec_int.empty ());
    EXPECT_EQ (vec_int.size (), 0);
}

TEST_F (Custom_vector_test, PushBack)
{
    vec_int.push_back (1);
    vec_int.push_back (2);
    vec_int.push_back (3);

    EXPECT_EQ (vec_int.size (), 3);
    EXPECT_EQ (vec_int[0], 1);
    EXPECT_EQ (vec_int[1], 2);
    EXPECT_EQ (vec_int[2], 3);
}

TEST_F (Custom_vector_test, PushBack_resize)
{
    vector::custom_vector<int> vec_int (1);
    vec_int.push_back (1);
    vec_int.push_back (2);
    vec_int.push_back (3);

    EXPECT_EQ (vec_int.size (), 3);
    EXPECT_EQ (vec_int[0], 1);
    EXPECT_EQ (vec_int[1], 2);
    EXPECT_EQ (vec_int[2], 3);
}

TEST_F (Custom_vector_test, PushBackValues)
{
    vec_int.push_back (10);
    vec_int.push_back (20);
    vec_int.push_back (30);

    EXPECT_EQ (vec_int.size (), 3);
    EXPECT_EQ (vec_int[0], 10);
    EXPECT_EQ (vec_int[1], 20);
    EXPECT_EQ (vec_int[2], 30);
}

TEST_F (Custom_vector_test, Erase)
{
    vec_int.push_back (1);
    vec_int.push_back (2);
    vec_int.push_back (3);
    vec_int.push_back (4);

    // Erase from middle
    vec_int.erase (1);
    EXPECT_EQ (vec_int.size (), 3);
    EXPECT_EQ (vec_int[0], 1);
    EXPECT_EQ (vec_int[1], 3);
    EXPECT_EQ (vec_int[2], 4);

    // Erase from beginning
    vec_int.erase (0);
    EXPECT_EQ (vec_int.size (), 2);
    EXPECT_EQ (vec_int[0], 3);
    EXPECT_EQ (vec_int[1], 4);

    // Erase from end
    vec_int.erase (1);
    EXPECT_EQ (vec_int.size (), 1);
    EXPECT_EQ (vec_int[0], 3);
}

TEST_F (Custom_vector_test, Insert)
{
    vec_int.push_back (1);
    vec_int.push_back (2);
    vec_int.push_back (3);

    // Insert at middle
    vec_int.insert (1, 10);
    EXPECT_EQ (vec_int.size (), 4);
    EXPECT_EQ (vec_int[0], 1);
    EXPECT_EQ (vec_int[1], 10);
    EXPECT_EQ (vec_int[2], 2);
    EXPECT_EQ (vec_int[3], 3);

    // Insert at beginning
    vec_int.insert (0, 0);
    EXPECT_EQ (vec_int.size (), 5);
    EXPECT_EQ (vec_int[0], 0);
    EXPECT_EQ (vec_int[1], 1);
    EXPECT_EQ (vec_int[2], 10);
    EXPECT_EQ (vec_int[3], 2);
    EXPECT_EQ (vec_int[4], 3);

    // Insert at end
    vec_int.insert (5, 4);
    EXPECT_EQ (vec_int.size (), 6);
    EXPECT_EQ (vec_int[0], 0);
    EXPECT_EQ (vec_int[1], 1);
    EXPECT_EQ (vec_int[2], 10);
    EXPECT_EQ (vec_int[3], 2);
    EXPECT_EQ (vec_int[4], 3);
    EXPECT_EQ (vec_int[5], 4);
}

TEST_F (Custom_vector_test, Clear)
{
    vec_int.push_back (1);
    vec_int.push_back (2);
    vec_int.push_back (3);

    EXPECT_EQ (vec_int.size (), 3);
    EXPECT_FALSE (vec_int.empty ());

    vec_int.clear ();

    EXPECT_EQ (vec_int.size (), 0);
    EXPECT_TRUE (vec_int.empty ());
}

TEST_F (Custom_vector_test, OperatorBracket)
{
    vec_int.push_back (1);
    vec_int.push_back (2);
    vec_int.push_back (3);

    // Check access by valid indices
    EXPECT_EQ (vec_int[0], 1);
    EXPECT_EQ (vec_int[1], 2);
    EXPECT_EQ (vec_int[2], 3);

    // Check access by invalid indices
    EXPECT_THROW (vec_int[3], std::out_of_range);
    EXPECT_THROW (vec_int[-1], std::out_of_range);
}

TEST_F (Custom_vector_test, CopyConstructor)
{
    vec_int.push_back (1);
    vec_int.push_back (2);
    vec_int.push_back (3);

    // Create copy
    vector::custom_vector<int> vec_copy (vec_int);

    // Check that copy contains the same elements
    EXPECT_EQ (vec_copy.size (), 3);
    EXPECT_EQ (vec_copy[0], 1);
    EXPECT_EQ (vec_copy[1], 2);
    EXPECT_EQ (vec_copy[2], 3);

    // Check that copy is independent from original
    vec_int.push_back (4);
    EXPECT_EQ (vec_int.size (), 4);
    EXPECT_EQ (vec_copy.size (), 3);
    EXPECT_EQ (vec_copy[0], 1);
    EXPECT_EQ (vec_copy[1], 2);
    EXPECT_EQ (vec_copy[2], 3);
}

TEST_F (Custom_vector_test, CopyAssignment)
{
    vec_int.push_back (1);
    vec_int.push_back (2);
    vec_int.push_back (3);

    vector::custom_vector<int> vec_copy;

    // Assignment
    vec_copy = vec_int;

    // Check that copy contains the same elements
    EXPECT_EQ (vec_copy.size (), 3);
    EXPECT_EQ (vec_copy[0], 1);
    EXPECT_EQ (vec_copy[1], 2);
    EXPECT_EQ (vec_copy[2], 3);

    // Check that copy is independent from original
    vec_int.push_back (4);
    EXPECT_EQ (vec_int.size (), 4);
    EXPECT_EQ (vec_copy.size (), 3);
    EXPECT_EQ (vec_copy[0], 1);
    EXPECT_EQ (vec_copy[1], 2);
    EXPECT_EQ (vec_copy[2], 3);
}

TEST_F (Custom_vector_test, MoveConstructor)
{
    vec_int.push_back (1);
    vec_int.push_back (2);
    vec_int.push_back (3);

    // Create by move
    vector::custom_vector<int> vec_move (std::move (vec_int));

    // Check that moved vector contains the same elements
    EXPECT_EQ (vec_move.size (), 3);
    EXPECT_EQ (vec_move[0], 1);
    EXPECT_EQ (vec_move[1], 2);
    EXPECT_EQ (vec_move[2], 3);

    // Check that original vector is empty
    EXPECT_EQ (vec_int.size (), 0);
    EXPECT_TRUE (vec_int.empty ());
}

TEST_F (Custom_vector_test, MoveAssignment)
{
    vector::custom_vector<int> vec_int;

    vec_int.push_back (1);
    vec_int.push_back (2);
    vec_int.push_back (3);

    vector::custom_vector<int> vec_move;

    // Assignment by move
    vec_move = std::move (vec_int);

    // Check that moved vector contains the same elements
    EXPECT_EQ (vec_move.size (), 3);
    EXPECT_EQ (vec_move[0], 1);
    EXPECT_EQ (vec_move[1], 2);
    EXPECT_EQ (vec_move[2], 3);

    // Check that original vector is empty
    EXPECT_EQ (vec_int.size (), 0);
    EXPECT_TRUE (vec_int.empty ());
}
