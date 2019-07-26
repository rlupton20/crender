#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include <matrix.h>
#include <pipeline.h>
#include <surface.h>
#include <texture.h>

typedef struct
{
  matrix4_t transform;
} transform_t;

vertex_t
rotation_shader(vertex_t vertex, const void* const data);

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
  render_pipeline_t pipeline = default_pipeline(&mesh, rotation_shader);

  float deg = 0;
  for (bool quit = false; !quit;) {

    for (SDL_Event e; !quit && SDL_PollEvent(&e) != 0;) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    transform_t transform = { .transform = rotateY(deg) };

    // Redraw the scene
    clear_screen(&screen, color(0, 0, 50));
    run_pipeline(&pipeline, &screen, (void*)&transform);

    // Update our render
    render(surface);

    deg += 0.1;
    SDL_Delay(10);
  }

  destroy_surface(surface);
  SDL_DestroyWindow(window);
  window = NULL;

  SDL_Quit();

  destroy_texture(texture);
  return 0;
}

vertex_t
rotation_shader(vertex_t vertex, const void* const data)
{
  transform_t* transform = (transform_t*)data;

  vec4_t pos = vec4(vertex.pos.x, vertex.pos.y, vertex.pos.z, 1);
  pos = mul(transform->transform, pos);
  vertex.pos = vec3(pos.x, pos.y, pos.z);

  return vertex;
}
