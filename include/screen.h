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

static inline void
set_pixel(screen_t* const screen, size_t x, size_t y, color_t color)
{
  // TODO Improve bounds check
  if (!(x < 0) && !(y < 0) && x < screen->width && y < screen->height)
    screen->pixel_buffer[y * screen->width + x] = color;
}

static inline float
aspect_ratio(const screen_t* const screen)
{
  return (screen->width) / (screen->height);
}
