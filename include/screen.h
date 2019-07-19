#pragma once
#include <stdlib.h>

#include <core.h>
#include <vector.h>

#include <assert.h>

typedef struct screen_t
{
  color_t* const pixel_buffer;
  const size_t width;
  const size_t height;
} screen_t;

void
clear_screen(screen_t* const screen, color_t color);

inline void
set_pixel(screen_t* const screen, size_t x, size_t y, color_t color)
{
  // TODO Improve bounds check
  assert(!(x < 0) && !(y < 0) && x < screen->width && y < screen->height);
  screen->pixel_buffer[y * screen->width + x] = color;
}

inline vec2_t
scale_normalised_coord(const screen_t* const screen, float x, float y)
{
  assert(!(x < -1) && !(y < -1) && !(x > 1) && !(y > 1));
  const size_t half_width = screen->width / 2;
  const size_t half_height = screen->height / 2;

  return vec2(half_width * (x + 1), half_height * (y + 1));
}
