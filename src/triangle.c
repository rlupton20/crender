#include <math.h>
#include <stdbool.h>

#include <triangle.h>

#define interpolate(barycentric_coords, a, b, c)                               \
  _Generic((a), vec2_t                                                         \
           : interpolate_vec2_t, vec3_t                                        \
           : interpolate_vec3_t)((barycentric_coords), (a), (b), (c))

static inline float
min(float a, float b)
{
  return a < b ? a : b;
}

static inline float
min3(float a, float b, float c)
{
  return min(a, min(b, c));
}

static inline float
max(float a, float b)
{
  return a < b ? b : a;
}

static inline float
max3(float a, float b, float c)
{
  return max(a, max(b, c));
}

/* l1 . a + l2 . b + (1 - l1 - l2) c */
static inline vec3_t
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

static inline vec4_t
bounding_box(const vec3_t a, const vec3_t b, const vec3_t c)
{
  return vec4(floor(min3(a.x, b.x, c.x)),
              floor(min3(a.y, b.y, c.y)),
              ceil(max3(a.x, b.x, c.x)),
              ceil(max3(a.y, b.y, c.y)));
}

static inline bool
inside_triangle(const vec3_t barycentric_coords)
{
  return barycentric_coords.x >= 0 && barycentric_coords.y >= 0 &&
         barycentric_coords.x + barycentric_coords.y <= 1;
}

static inline vec2_t
interpolate_vec2_t(vec3_t barycentric_coords, vec2_t a, vec2_t b, vec2_t c)
{
  const float l1 = barycentric_coords.x;
  const float l2 = barycentric_coords.y;
  const float l3 = barycentric_coords.z;
  return vec2(a.x * l1 + b.x * l2 + c.x * l3, a.y * l1 + b.y * l2 + c.y * l3);
}

static inline vec3_t
interpolate_vec3_t(vec3_t barycentric_coords, vec3_t a, vec3_t b, vec3_t c)
{
  const float l1 = barycentric_coords.x;
  const float l2 = barycentric_coords.y;
  const float l3 = barycentric_coords.z;
  return vec3(a.x * l1 + b.x * l2 + c.x * l3,
              a.y * l1 + b.y * l2 + c.y * l3,
              a.z * l1 + b.z * l2 + c.z * l3);
}

void
draw_triangle_xy(screen_t* const screen,
                 const texture_t* const texture,
                 fragment_shader_t* const fragment_shader,
                 const vertex_t a,
                 const vertex_t b,
                 const vertex_t c)
{
  const vec4_t box = bounding_box(a.pos, b.pos, c.pos);

  for (size_t x = box.x; x <= box.z; ++x) {
    for (size_t y = box.y; y <= box.w; ++y) {
      const vec3_t coords = get_barycentric_coords(x, y, a.pos, b.pos, c.pos);

      if (inside_triangle(coords)) {
        const vec2_t sample =
          interpolate(coords, a.surface, b.surface, c.surface);
        const vec3_t normal = interpolate(coords, a.normal, b.normal, c.normal);
        color_t color = fragment_shader(
          sample_texture(texture, sample.x, sample.y), normal, NULL);
        set_pixel(screen, x, y, color);
      }
    }
  }
}
