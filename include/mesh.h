#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include <texture.h>
#include <vertex.h>

typedef struct mesh_t mesh_t;
typedef struct mesh_iter_t mesh_iter_t;

struct mesh_t
{
  float* const vertex_data;  /* Data describing vertices */
  const size_t num_vertices; /* The number of vertices represented */
  const size_t stride;   /* The number of floating point numbers per vertex */
  size_t* const indices; /* A sequence of vertices forming a mesh */
  const size_t num_indices; /* Number of vertices in sequence forming a mesh */
  const texture_t* const texture;
};

struct mesh_iter_t
{
  const mesh_t* const mesh; /* Pointer to a mesh */
  size_t current;           /* Current index of vertex */
};

mesh_iter_t
mesh_iterator(const mesh_t* const mesh);

/*
 * The number of vertices beyond the current we can iterate to
 */
size_t
remaining(const mesh_iter_t* const iter);

/*
 * Advance the iterator, returning true on successful
 * advancement. false is returned when the end of the list is
 * reached.
 */
bool
next(mesh_iter_t* const iter);

/*
 * Extract the vertex pointed to by the iterator
 */
vertex_t
get_vertex(const mesh_iter_t* const iter);

/*
 * Demo example
 */

mesh_t
example_mesh(const texture_t* const texture);
