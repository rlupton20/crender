#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include <surface.h>
#include <vector.h>

#include <triangle.h>

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

  const vec3_t a = vec3(100, 500, 10);
  const vec3_t b = vec3(700, 500, 10);
  const vec3_t c = vec3(400, 100, 10);

  for (bool quit = false; !quit;) {

    for (SDL_Event e; !quit && SDL_PollEvent(&e) != 0;) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    clear_screen(&screen, color(0, 0, 50));
    draw_triangle_xy(&screen, a, b, c);

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
