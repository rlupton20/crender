#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include <surface.h>
#include <vector.h>
#include <vertex.h>

#include <triangle.h>

/*
 * Populate three vertices to form a triangle.
 *
 * Returns true if and only if it succeeds, and false otherwise
 * leaving the vertices unchanged.
 */
bool
get_triangle(mesh_iter_t* const iter,
             vertex_t* const a,
             vertex_t* const b,
             vertex_t* const c);

int
main(int argc, char* argv[])
{
  const size_t width = 800;
  const size_t height = 600;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("Failed to initialize SDL\n");
    return 1;
  }

  SDL_Window* window = SDL_CreateWindow("renderer",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        width,
                                        height,
                                        SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("Failed to create SDL window\n");
    return 1;
  }

  surface_t* surface = new_surface(window);
  screen_t screen = get_screen(surface);

  mesh_t mesh = example_mesh();
  vertex_t a = { 0 }, b = { 0 }, c = { 0 };

  for (bool quit = false; !quit;) {

    for (SDL_Event e; !quit && SDL_PollEvent(&e) != 0;) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    clear_screen(&screen, color(0, 0, 50));

    for (mesh_iter_t iterator = mesh_iterator(&mesh);
         get_triangle(&iterator, &a, &b, &c);) {
      draw_triangle_xy(&screen, a.pos, b.pos, c.pos);
    }

    // Update our render
    render(surface);
    SDL_Delay(10);
  }

  destroy_surface(surface);
  SDL_DestroyWindow(window);
  window = NULL;

  SDL_Quit();
  return 0;
}

bool
get_triangle(mesh_iter_t* const iter,
             vertex_t* const a,
             vertex_t* const b,
             vertex_t* const c)
{
  if (remaining(iter) < 2) {
    return false;
  }

  vertex_t* vertices[3] = { a, b, c };
  for (size_t ix = 0; ix < 3; ++ix) {
    *(vertices[ix]) = get_vertex(iter);
    next(iter);
  }

  return true;
}
