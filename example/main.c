#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include <pipeline.h>
#include <surface.h>
#include <texture.h>

int
main(int argc, char* argv[])
{
  if (argc < 2) {
    printf("Need to specify image\n");
    return 1;
  }

  const char* const texture_file = argv[1];
  texture_t* const texture = texture_from_file(texture_file);
  if (!texture) {
    printf("Error loading texture '%s'!\n", texture_file);
    return 1;
  }

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
  mesh_t mesh = example_mesh(texture);
  render_pipeline_t pipeline = default_pipeline(&mesh);

  for (bool quit = false; !quit;) {

    for (SDL_Event e; !quit && SDL_PollEvent(&e) != 0;) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    // Redraw the scene
    clear_screen(&screen, color(0, 0, 50));
    run_pipeline(&pipeline, &screen);

    // Update our render
    render(surface);
    SDL_Delay(10);
  }

  destroy_surface(surface);
  SDL_DestroyWindow(window);
  window = NULL;

  SDL_Quit();

  destroy_texture(texture);
  return 0;
}
