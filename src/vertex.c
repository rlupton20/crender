#include <vertex.h>

size_t
offset(const mesh_iter_t* const iter);

mesh_iter_t
mesh_iterator(const mesh_t* const mesh)
{
  return (mesh_iter_t){ .mesh = mesh, .current = 0 };
}

size_t
remaining(const mesh_iter_t* const iter)
{
  return iter->mesh->num_indices - iter->current - 1;
}

bool
next(mesh_iter_t* const iter)
{
  if (remaining(iter) > 0) {
    iter->current++;
    return true;
  } else {
    return false;
  }
}

vertex_t
get_vertex(const mesh_iter_t* const iter)
{
  vertex_t v = { 0 };
  const float* const base = iter->mesh->vertex_data + offset(iter);
  v.pos = vec3(base[0], base[1], base[2]);
  v.surface = vec2(base[3], base[4]);
  return v;
}

size_t
offset(const mesh_iter_t* const iter)
{
  return iter->mesh->indices[iter->current] * iter->mesh->stride;
}

/*
 * Demo example
 */
/* clang-format off */
static float vertices[] = { 100, 500, 10, 0, 0,
                            700, 500, 10, 1, 0,
                            400, 100, 10 ,0.5, 1};
static size_t indices[] = { 0, 1, 2 };
/* clang-format on */

mesh_t
example_mesh()
{
  return (mesh_t){ .vertex_data = vertices,
                   .num_vertices = 3,
                   .stride = 5,
                   .indices = indices,
                   .num_indices = 3 };
}
