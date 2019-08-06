#pragma once

#include <stdint.h>

typedef uint32_t color_t;

inline color_t
color(uint8_t r, uint8_t g, uint8_t b)
{
  return (r << 16 | g << 8 | b);
}

inline color_t
multiply(color_t color, float factor)
{
  uint8_t* const color8 = (uint8_t*)&color;
  for (size_t ix = 0; ix < 4; ++ix) {
    color8[ix] = color8[ix] * factor;
  }
  return color;
}
