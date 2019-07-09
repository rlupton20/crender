#include <screen.h>

void
clear_screen(screen_t* const screen, color_t color)
{
  for(size_t y = 0; y < screen->height; ++y)
    for(size_t x = 0; x < screen->width; ++x)
      set_pixel(screen, x, y, color);
}
