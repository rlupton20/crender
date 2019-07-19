#pragma once

#include <screen.h>
#include <texture.h>
#include <vertex.h>

void
draw_triangle_xy(screen_t* const screen,
                 const texture_t* const texture,
                 const vertex_t a,
                 const vertex_t b,
                 const vertex_t c);
