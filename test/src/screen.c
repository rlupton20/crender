#include <test.h>

#include <screen.h>
#include <vector.h>

bool
test_projective_cube_to_screen()
{
  const screen_t screen =
    (screen_t){ .pixel_buffer = NULL, .width = 800, .height = 600 };
  (void)screen;

  {
    const vec2_t result = projective_cube_to_screen(&screen, 1.0, 1.0);
    ASSERT(result.x == 800);
    ASSERT(result.y == 600);
  }

  {
    const vec2_t result = projective_cube_to_screen(&screen, 0.0, 0.0);
    ASSERT(result.x == 400);
    ASSERT(result.y == 300);
  }

  {
    const vec2_t result = projective_cube_to_screen(&screen, -1.0, -1.0);
    ASSERT(result.x == 0);
    ASSERT(result.y == 0);
  }

  return true;
}
