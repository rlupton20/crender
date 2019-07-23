#pragma once

#include <vector.h>
#include <stdlib.h>

typedef struct
{
  const float elems[16];
} matrix4_t;

inline matrix4_t
identity_matrix() {
  return (matrix4_t) {
    /* clang-format off */
    .elems = {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    }
    /* clang-format on */
  };
}

inline float
matrix_element(matrix4_t m, size_t row, size_t column)
{
  return m.elems[4 * row + column];
}
