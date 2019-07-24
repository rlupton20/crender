#pragma once

#define dot(a, b) dot_vec4_t((a), (b))

typedef struct vec2_t
{
  float x;
  float y;
} vec2_t;

typedef struct vec3_t
{
  float x;
  float y;
  float z;
} vec3_t;

typedef struct vec4_t
{
  float x;
  float y;
  float z;
  float w;
} vec4_t;

inline vec2_t
vec2(float x, float y)
{
  return (vec2_t){ x, y };
}

inline vec3_t
vec3(float x, float y, float z)
{
  return (vec3_t){ x, y, z };
}

inline vec4_t
vec4(float x, float y, float z, float w)
{
  return (vec4_t){ x, y, z, w };
}

inline vec4_t*
vec4_from_floats(const float* const elems)
{
  return (vec4_t*)elems;
}

inline float
dot_vec4_t(const vec4_t a, const vec4_t b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
