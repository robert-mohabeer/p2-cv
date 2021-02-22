// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.

TEST(test_fill_equal) {
    Matrix* mat = new Matrix;
    Matrix* mat2 = new Matrix;

    const int width = 56;
    const int height = 24;
    const int value = 11;
    Matrix_init(mat, width, height);
    Matrix_init(mat2, width, height);
    Matrix_fill(mat2, value);

    ASSERT_FALSE(Matrix_equal(mat, mat2));

    delete mat; // delete the Matrix
}

TEST(test_fill_border) {
    Matrix* mat = new Matrix;

    const int width = 10;
    const int height = 10;
    const int value = 1;
    Matrix_init(mat, width, height);
    Matrix_fill_border(mat, value);

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            if (x == 0 || x == height - 1 || y == 0 || y == width - 1)
            {
                ASSERT_EQUAL(*Matrix_at(mat, x, y), value);
            }
        }
    }

    delete mat; // delete the Matrix
}

TEST(test_max) {
    Matrix* mat = new Matrix;

    const int width = 10;
    const int height = 10;
    int col_max = 5;
    int row_max = 5;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            *Matrix_at(mat, x, y) = 13;
        }
    }
    *Matrix_at(mat, row_max, col_max) = 144;
    ASSERT_EQUAL(Matrix_max(mat), 144);

    delete mat; // delete the Matrix
}
TEST_MAIN() // Do NOT put a semicolon here
