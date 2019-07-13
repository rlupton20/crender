#pragma once
#include <stdlib.h>

#include <core.h>

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
  // TODO Add bounds check
  screen->pixel_buffer[y * screen->width + x] = color;
}
