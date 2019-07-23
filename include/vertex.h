#pragma once

#include <vector.h>

typedef struct vertex_t
{
  vec3_t pos;     /* Position vector */
  vec2_t surface; /* Surface coordinate, for e.g. texture */
  vec3_t normal;  /* Direction of normal to surface */
} vertex_t;
