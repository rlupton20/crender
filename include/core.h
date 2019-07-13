#pragma once

#include <stdint.h>

typedef uint32_t color_t;

inline color_t
color(uint8_t r, uint8_t g, uint8_t b)
{
  return (r << 16 | g << 8 | b);
}
