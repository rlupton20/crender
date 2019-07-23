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

void
run_pipeline(const render_pipeline_t* const pipeline, screen_t* const screen)
{
  vertex_t a = { 0 }, b = { 0 }, c = { 0 };
  for (mesh_iter_t iterator = pipeline->new_mesh_iter(pipeline->mesh);
       get_triangle(&iterator, &a, &b, &c);) {
    draw_triangle_xy(screen, pipeline->mesh->texture, a, b, c);
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
