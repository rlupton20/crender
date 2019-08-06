#include <pipeline.h>
#include <triangle.h>

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

inline void
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

    draw_triangle_xy(
      screen, pipeline->mesh->texture, pipeline->fragment_shader, a, b, c);
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
