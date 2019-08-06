#pragma once

#include <pipeline.h>
#include <screen.h>
#include <texture.h>
#include <vertex.h>

void
draw_triangle_xy(screen_t* const screen,
                 const texture_t* const texture,
                 fragment_shader_t* const fragment_shader,
                 const vertex_t a,
                 const vertex_t b,
                 const vertex_t c);
