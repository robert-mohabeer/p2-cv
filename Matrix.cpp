// Project UID af1f95f547e44c8ea88730dfb185559ds

#include <cassert>
#include "Matrix.h"
using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
    assert(width > 0 && width < MAX_MATRIX_WIDTH); 
    assert(height > 0 && height < MAX_MATRIX_HEIGHT);
    mat->height = height;
    mat->width = width;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {

    os << mat->width << " ";
    os << mat->height << endl;
    for (int x = 0; x < mat->height; x++)
    {
        for (int y = 0; y < mat->width; y++)
        {
            os << mat->data[y + x * mat->width] << " ";
        }
        os << endl;
    }
  //assert(false);
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  assert(mat->width > 0);
    return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  assert(mat->height > 0); 
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  assert(mat->height > 0 && mat->width > 0);
  assert(ptr >= &mat->data[0] && ptr <= &mat->data[mat->height * mat->width -1]);
  int dist = ptr - &mat->data[0];
  return dist / mat->width;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
    assert(mat->height > 0 && mat->width > 0);
    assert(ptr >= &mat->data[0] && ptr <= &mat->data[mat->height * mat->width - 1]);
    int dist = ptr - &mat->data[0];
    return dist % mat->width;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  assert(row >= 0 && column >= 0);
  assert(row < Matrix_height(mat) && column < Matrix_width(mat));
  int steps = row * Matrix_width(mat) + column;
  return &mat->data[steps];
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
    assert(row >= 0 && column >= 0);
    assert(row < Matrix_height(mat) && column < Matrix_width(mat));
    int steps = row * Matrix_width(mat) + column;
    return &mat->data[steps];
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
    assert(mat->height > 0 && mat->width > 0);
    for (int x = 0; x < mat->height; x++)
    {
        for (int y = 0; y < mat->width; y++)
        {
            *Matrix_at(mat, x, y) = value;
        }
    }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  assert(mat->height > 0 && mat ->width > 0);
  for (int x = 0; x < mat->height; x++)
  {
      for (int y = 0; y < mat->width; y++)
      {
          if (x == 0 || x == mat->height - 1 || y == 0 || y == mat->width-1)
          {
              *Matrix_at(mat, x, y) = value;
          }
      }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
    int max = 0;
    for (int x = 0; x < mat->height; x++)
    {
        for (int y = 0; y < mat->width; y++)
        {
            if (*Matrix_at(mat, x, y) > max)
            {
                max = *Matrix_at(mat, x, y);
            }
        }
    }
  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  assert(mat->height > 0 && mat->width > 0);
  assert(column_start >= 0 && column_start < Matrix_width(mat) && column_start < column_end);
  assert(row >= 0 && row < Matrix_height(mat));
  assert(column_end <= Matrix_width(mat));

  int diff = column_end - column_start;
  const int* start = Matrix_at(mat, row, column_start);
  int min = *start;
  int colMin = column_start;
  while (diff != 1)
  {
      ++start;
      --diff;
      if (*start < min)
      {
          min = *start;
          colMin = Matrix_column(mat, start);
      }
  }
  return colMin;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
    assert(mat->height > 0 && mat->width > 0);
    assert(column_start >= 0 && column_start < Matrix_width(mat) && column_start < column_end);
    assert(row >= 0 && row < Matrix_height(mat));
    assert(column_end <= Matrix_width(mat));

    int diff = column_end - column_start;
    const int* start = Matrix_at(mat, row, column_start);
    int min = *start;
    while (diff != 1)
    {
        ++start;
        --diff;
        if (*start < min)
        {
            min = *start;
        }
    }
    return min;
}
