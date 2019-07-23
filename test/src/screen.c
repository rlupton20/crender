#include <test.h>

#include <screen.h>
#include <vector.h>

bool
test_projective_cube_to_screen()
{
  const screen_t screen =
    (screen_t){ .pixel_buffer = NULL, .width = 800, .height = 600 };
  (void)screen;
  return true;
}
