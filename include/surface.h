#pragma once

#pragma once
#include <SDL2/SDL.h>

typedef struct surface_t surface_t;

surface_t*
new_surface(SDL_Window* window);

void
destroy_surface(surface_t* surface);

void
render(const surface_t* surface);
