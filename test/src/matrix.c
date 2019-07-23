#include <matrix.h>
#include <test.h>

bool
test_matrix_element();

bool
test_matrices()
{
  RUN_TEST(test_matrix_element);
  return true;
}

bool
test_matrix_element()
{
  matrix4_t id = identity_matrix();

  for (size_t ix = 0; ix < 4; ++ix)
    for (size_t jx = 0; jx < 4; ++jx){
      if (ix == jx) {
        ASSERT(matrix_element(id, ix, jx) == 1);
      } else {
        ASSERT(matrix_element(id, ix, jx) == 0);
      }
    }

  return true;
}
