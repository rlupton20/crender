#pragma once

#include <SDL2/SDL.h>

#include <screen.h>

typedef struct surface_t surface_t;

surface_t*
new_surface(SDL_Window* window);

void
destroy_surface(surface_t* surface);

void
render(const surface_t* surface);

screen_t
get_screen(const surface_t* const surface);
