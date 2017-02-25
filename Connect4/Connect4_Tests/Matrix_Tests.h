#include "gtest/gtest.h"
#include "Matrix.h"

TEST(MatrixTests, Constructor)
{
    Matrix a = Matrix(6, 7);
    EXPECT_EQ(a.NumRow, 6);
    EXPECT_EQ(a.NumCol, 7);
}

TEST(MatrixTests, CopyAssignment)
{
    Matrix a = Matrix(5, 6);

    Matrix b = a;
    EXPECT_EQ(b.NumRow, 5);
    EXPECT_EQ(b.NumCol, 6);


    a(4, 4) = 4;
    EXPECT_EQ(a(4, 4), 4);
    EXPECT_EQ(b(4, 4), 0);  //Expect change in a to not affect b

    Matrix* a_ptr = new Matrix(5, 6);
    Matrix* b_ptr = new Matrix(*a_ptr);
    (*a_ptr)(4, 4) = 4;
    EXPECT_EQ((*a_ptr)(4, 4), 4);
    EXPECT_EQ((*b_ptr)(4, 4), 0);

    //Test structure is copied across
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            a(i, j) = i*a.NumCol + j;
            EXPECT_EQ(a(i, j), i*a.NumCol + j);
        }
    }

    Matrix c = a;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            EXPECT_EQ(c(i, j), i*a.NumCol + j);
        }
    }
}

TEST(MatrixTests, OutOfBoundsAccess)
{
    Matrix a = Matrix(5, 5);
    EXPECT_THROW(a(5, 5) = 4, std::exception);
    EXPECT_THROW(a(5, 4) = 4, std::exception);
    EXPECT_THROW(a(4, 5) = 4, std::exception);
    EXPECT_NO_THROW(a(4, 4) = 4);
    EXPECT_NO_THROW(a(0, 0) = 4);
}