#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include <vector.h>

#define vec_eq(l, r) vec4_t_eq((l), (r))

typedef struct
{
  const float elems[16];
} matrix4_t;

inline matrix4_t
identity_matrix()
{
  return (matrix4_t){
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

inline vec4_t
row(matrix4_t m, size_t n)
{
  return *vec4_from_floats(m.elems + 4 * n);
}

inline vec4_t
mul_mat4_vec4(const matrix4_t m, const vec4_t v)
{
  return vec4(
    dot(row(m, 0), v), dot(row(m, 1), v), dot(row(m, 2), v), dot(row(m, 3), v));
}

inline bool
vec4_t_eq(vec4_t l, vec4_t r)
{
  return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
}
