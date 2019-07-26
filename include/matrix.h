#pragma once

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <vector.h>

#define equal(l, r)                                                            \
  _Generic((l), vec4_t : vec4_t_eq, matrix4_t : matrix4_t_eq)((l), (r))

/* clang-format off */
#define mul(l, r)                                                              \
  _Generic((l),                                                                \
           matrix4_t : _Generic((r),                                           \
                                vec4_t : _multiply_matrix4_t_vec4_t,           \
                                matrix4_t : _multiply_matrix4_t))((l), (r))
/* clang-format on */

static const float pi = 3.14159;

typedef struct
{
  float elems[16];
} matrix4_t;

static inline matrix4_t
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

inline matrix4_t
zero_matrix()
{
  return (matrix4_t){ 0 };
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
_multiply_matrix4_t_vec4_t(const matrix4_t m, const vec4_t v)
{
  return vec4(
    dot(row(m, 0), v), dot(row(m, 1), v), dot(row(m, 2), v), dot(row(m, 3), v));
}

inline bool
vec4_t_eq(vec4_t l, vec4_t r)
{
  return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
}

#define elem(m, r, c) ((m).elems)[(r)*4 + (c)]
matrix4_t
_multiply_matrix4_t(const matrix4_t l, const matrix4_t r)
{
  matrix4_t ret = zero_matrix();

  for (size_t row = 0; row < 4; ++row)
    for (size_t col = 0; col < 4; ++col) {
      elem(ret, row, col) =
        elem(l, row, 0) * elem(r, 0, col) + elem(l, row, 1) * elem(r, 1, col) +
        elem(l, row, 2) * elem(r, 2, col) + elem(l, row, 3) * elem(r, 3, col);
    }
  return ret;
}
#undef elem

inline bool
matrix4_t_eq(const matrix4_t l, const matrix4_t r)
{
  return (memcmp(l.elems, r.elems, 16) == 0);
}

matrix4_t
rotateY(float deg)
{
  return (matrix4_t){
    /* clang-format off */
    .elems = {
      cosf(deg), 0, sinf(deg), 0,
      0, 1, 0, 0,
      - sinf(deg), 0, cosf(deg), 0,
      0, 0, 0, 1
    }
    /* clang-format on */
  };
}

static inline matrix4_t
translateZ(float mov)
{
  return (matrix4_t){
    /* clang-format off */
    .elems = {
              1, 0, 0, 0,
              0, 1, 0, 0,
              0, 0, 1, mov,
              0, 0, 0, 1
              }
    /* clang-format on */
  };
}

static inline matrix4_t
projection_matrix(const float fov,
                  const float aspect_ratio,
                  const float z_near,
                  const float z_far)
{
  const float rads = fov * pi / 180;
  float fov_scale = tanf(rads / 2);
  // z \mapsto A + Bz
  const float A = 2 * z_far * z_near / (z_near - z_far);
  const float B = (z_far - z_near) / (z_far + z_near);
  return (matrix4_t){
    /* clang-format off */
    .elems = {
              1 / (aspect_ratio * fov_scale), 0, 0, 0,
              0,      1 / fov_scale, 0, 0,
              0,      0, B, A,
              0,      0, 1, 0
    }
    /* clang-format on */
  };
}
