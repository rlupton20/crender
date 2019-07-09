#pragma once
#include <stdint.h>
#include <stdlib.h>

typedef struct screen_t
{
  uint32_t* const pixel_buffer;
  const size_t width;
  const size_t height;
} screen_t;

typedef uint32_t color_t;

void
clear_screen(screen_t* const screen, color_t color);

inline color_t
color(uint8_t r, uint8_t g, uint8_t b)
{
  return (r << 16 | g << 8 | b);
}

inline void
set_pixel(screen_t* const screen, size_t x, size_t y, color_t color)
{
  // TODO Add bounds check
  screen->pixel_buffer[y * screen->width + x] = color;
}
