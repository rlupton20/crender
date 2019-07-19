#include <test.h>

#include <screen.h>
#include <vector.h>

bool
test_scale_normalised_coord()
{
  const screen_t screen =
    (screen_t){ .pixel_buffer = NULL, .width = 800, .height = 600 };
  (void)screen;

  {
    const vec2_t result = scale_normalised_coord(&screen, 1.0, 1.0);
    ASSERT(result.x == 800);
    ASSERT(result.y == 600);
  }

  {
    const vec2_t result = scale_normalised_coord(&screen, 0.0, 0.0);
    ASSERT(result.x == 400);
    ASSERT(result.y == 300);
  }

  {
    const vec2_t result = scale_normalised_coord(&screen, -1.0, -1.0);
    ASSERT(result.x == 0);
    ASSERT(result.y == 0);
  }

  return true;
}
