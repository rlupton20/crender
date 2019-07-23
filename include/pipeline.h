#pragma once

#include <screen.h>
#include <vertex.h>

typedef vertex_t(vertex_source_t)(const mesh_iter_t* const iter);
typedef mesh_iter_t(mesh_iter_builder_t)(const mesh_t* const mesh);

typedef struct render_pipeline_t
{
  const mesh_t* const mesh;
  mesh_iter_builder_t* new_mesh_iter;
  vertex_source_t* vertex_source;
} render_pipeline_t;

inline render_pipeline_t
default_pipeline(const mesh_t* const mesh)
{
  return (render_pipeline_t){ .mesh = mesh,
                              .new_mesh_iter = mesh_iterator,
                              .vertex_source = get_vertex };
}

void
run_pipeline(const render_pipeline_t* const pipeline, screen_t* const screen);
