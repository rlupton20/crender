#include <surface.h>

struct surface_t
{
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  uint32_t* pixels;
  size_t height;
  size_t width;
};

surface_t*
new_surface(SDL_Window* window)
{
  int width = 0, height = 0;
  SDL_GetWindowSize(window, &width, &height);

  surface_t* ret = calloc(1, sizeof(surface_t));

  if (ret == NULL) {
    return NULL;
  }

  uint32_t* const pixels = calloc(height * width, sizeof(uint32_t));

  if (pixels == NULL) {
    free(ret);
    return NULL;
  }

  ret->renderer = SDL_CreateRenderer(window, -1, 0);
  ret->texture = SDL_CreateTexture(ret->renderer,
                                   SDL_PIXELFORMAT_ARGB8888,
                                   SDL_TEXTUREACCESS_STATIC,
                                   width,
                                   height);
  ret->pixels = pixels;
  ret->height = height;
  ret->width = width;
  return ret;
}

void
destroy_surface(surface_t* surface)
{
  SDL_DestroyTexture(surface->texture);
  surface->texture = NULL;
  SDL_DestroyRenderer(surface->renderer);
  surface->renderer = NULL;
}

void
render(const surface_t* surface)
{
  SDL_UpdateTexture(
    surface->texture, NULL, surface->pixels, surface->width * sizeof(uint32_t));
  SDL_RenderClear(surface->renderer);
  SDL_RenderCopy(surface->renderer, surface->texture, NULL, NULL);
  SDL_RenderPresent(surface->renderer);
}
