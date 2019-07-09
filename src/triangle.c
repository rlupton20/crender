#include <math.h>
#include <stdbool.h>

#include <triangle.h>

inline float
min(float a, float b)
{
  return a < b ? a : b;
}

inline float
min3(float a, float b, float c)
{
  return min(a, min(b, c));
}

inline float
max(float a, float b)
{
  return a < b ? b : a;
}

inline float
max3(float a, float b, float c)
{
  return max(a, max(b, c));
}

inline vec3_t
get_barycentric_coords(size_t x,
                       size_t y,
                       const vec3_t a,
                       const vec3_t b,
                       const vec3_t c)
{
  const float det = (b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y);
  const float l1 = ((b.y - c.y) * (x - c.x) + (c.x - b.x) * (y - c.y)) / det;
  const float l2 = ((c.y - a.y) * (x - c.x) + (a.x - c.x) * (y - c.y)) / det;
  return vec3(l1, l2, 1 - l1 - l2);
}

inline vec4_t
bounding_box(const vec3_t a, const vec3_t b, const vec3_t c)
{
  return vec4(floor(min3(a.x, b.x, c.x)),
              floor(min3(a.y, b.y, c.y)),
              ceil(max3(a.x, b.x, c.x)),
              ceil(max3(a.y, b.y, c.y)));
}

inline bool
inside_triangle(const vec3_t barycentric_coords)
{
  return barycentric_coords.x >= 0 && barycentric_coords.y >= 0 &&
         barycentric_coords.x + barycentric_coords.y <= 1;
}

void
draw_triangle_xy(screen_t* const screen,
                 const vec3_t a,
                 const vec3_t b,
                 const vec3_t c)
{
  const vec4_t box = bounding_box(a, b, c);

  for (size_t x = box.x; x <= box.z; ++x) {
    for (size_t y = box.y; y <= box.w; ++y) {
      const vec3_t coords = get_barycentric_coords(x, y, a, b, c);

      if (inside_triangle(coords)) {
        set_pixel(screen, x, y, color(255, 255, 255));
      }
    }
  }
}
