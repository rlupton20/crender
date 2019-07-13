#pragma once

#include <core.h>

typedef struct texture_t texture_t;

texture_t*
texture_from_file(const char* const file);

void
destroy_texture(texture_t* const texture);

color_t
sample_texture(const texture_t* const texture, float x, float y);
