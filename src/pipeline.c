#include <math.h>
#include <stdbool.h>

#include <pipeline.h>
#include <texture.h>

#define interpolate(barycentric_coords, a, b, c)                               \
  _Generic((a), vec2_t                                                         \
           : interpolate_vec2_t, vec3_t                                        \
           : interpolate_vec3_t)((barycentric_coords), (a), (b), (c))

/*
 * Populate three vertices to form a triangle.
 *
 * Returns true if and only if it succeeds, and false otherwise
 * leaving the vertices unchanged.
 */
bool
get_triangle(mesh_iter_t* const iter,
             vertex_t* const a,
             vertex_t* const b,
             vertex_t* const c);

/*
 * Draw a triangle to screen.
 */
static void
draw_triangle_xy(screen_t* const screen,
                 const texture_t* const texture,
                 fragment_shader_t* const fragment_shader,
                 const void* const data,
                 const vertex_t a,
                 const vertex_t b,
                 const vertex_t c);

static inline void
scale_to_screen(const screen_t* const screen, vertex_t* const v)
{
  const size_t half_width = screen->width / 2;
  const size_t half_height = screen->height / 2;
  v->pos.x = half_width * (v->pos.x + 1);
  v->pos.y = half_height * (1 - v->pos.y);
  return;
}

void
run_pipeline(const render_pipeline_t* const pipeline,
             screen_t* const screen,
             const void* const data)
{
  vertex_t a = { 0 }, b = { 0 }, c = { 0 };
  for (mesh_iter_t iterator = pipeline->new_mesh_iter(pipeline->mesh);
       get_triangle(&iterator, &a, &b, &c);) {

    a = (pipeline->vertex_shader)(a, data);
    b = (pipeline->vertex_shader)(b, data);
    c = (pipeline->vertex_shader)(c, data);

    scale_to_screen(screen, &a);
    scale_to_screen(screen, &b);
    scale_to_screen(screen, &c);

    draw_triangle_xy(screen,
                     pipeline->mesh->texture,
                     pipeline->fragment_shader,
                     data,
                     a,
                     b,
                     c);
  }
}

bool
get_triangle(mesh_iter_t* const iter,
             vertex_t* const a,
             vertex_t* const b,
             vertex_t* const c)
{
  if (remaining(iter) < 2) {
    return false;
  }

  vertex_t* vertices[3] = { a, b, c };
  for (size_t ix = 0; ix < 3; ++ix) {
    *(vertices[ix]) = get_vertex(iter);
    next(iter);
  }

  return true;
}

vertex_t
identity_shader(vertex_t vertex, const void* const data)
{
  return vertex;
}

/*
 * Functions to help draw triangles to screen
 */

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
                 const void* const data,
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
