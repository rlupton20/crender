#pragma once

#include <mesh.h>
#include <screen.h>

typedef vertex_t(vertex_source_t)(const mesh_iter_t* const iter);
typedef mesh_iter_t(mesh_iter_builder_t)(const mesh_t* const mesh);
typedef vertex_t(vertex_shader_t)(vertex_t vertex, const void* const data);

vertex_t
identity_shader(vertex_t vertex, const void* const data);

typedef struct render_pipeline_t
{
  const mesh_t* const mesh;
  mesh_iter_builder_t* new_mesh_iter;
  vertex_source_t* vertex_source;
  vertex_shader_t* vertex_shader;
} render_pipeline_t;

static inline render_pipeline_t
default_pipeline(const mesh_t* const mesh, vertex_shader_t* vertex_shader)
{
  return (render_pipeline_t){ .mesh = mesh,
                              .new_mesh_iter = mesh_iterator,
                              .vertex_source = get_vertex,
                              .vertex_shader = vertex_shader };
}

void
run_pipeline(const render_pipeline_t* const pipeline,
             screen_t* const screen,
             const void* const data);
