#include <matrix.h>
#include <test.h>

bool
test_matrix_element();

bool
test_vector_row_cast();

bool
test_vector_dot_product();

bool
test_mul_mat4_vec4();

bool
test_mul_mat4();

bool
test_matrices()
{
  RUN_TEST(test_matrix_element);
  RUN_TEST(test_vector_row_cast);
  RUN_TEST(test_vector_dot_product);
  RUN_TEST(test_mul_mat4_vec4);
  RUN_TEST(test_mul_mat4);
  return true;
}

bool
test_matrix_element()
{
  matrix4_t id = identity_matrix();

  for (size_t ix = 0; ix < 4; ++ix)
    for (size_t jx = 0; jx < 4; ++jx) {
      if (ix == jx) {
        ASSERT(matrix_element(id, ix, jx) == 1);
      } else {
        ASSERT(matrix_element(id, ix, jx) == 0);
      }
    }

  return true;
}

// TODO Make a vector test suite
bool
test_vector_row_cast()
{
  matrix4_t id = identity_matrix();
  vec4_t* v = vec4_from_floats(id.elems);
  ASSERT(v->x == 1);
  ASSERT(v->y == 0);
  ASSERT(v->z == 0);
  ASSERT(v->w == 0);

  return true;
}

bool
test_vector_dot_product()
{
  vec4_t v = vec4(1, 1, 1, 1);
  ASSERT(dot(v, v) == 4);
  return true;
}

bool
test_mul_mat4_vec4()
{
  const matrix4_t id = identity_matrix();
  const vec4_t v = vec4(1, 2, 3, 4);
  const vec4_t result = mul_mat4_vec4(id, v);
  ASSERT(vec_eq(v, result));
  return true;
}

bool
test_mul_mat4()
{
  const matrix4_t id = identity_matrix();
  ASSERT(matrix4_t_eq(id, mul_mat4(id, id)));
  return true;
}
