#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include <texture.h>

static const size_t num_components = 4;

struct texture_t
{
  uint8_t* data;
  size_t width;
  size_t height;
};

texture_t*
texture_from_file(const char* const file)
{
  int width = 0, height = 0, components = 0;
  uint8_t* const data =
    stbi_load(file, &width, &height, &components, num_components);

  if (!data) {
    return NULL;
  }

  texture_t* const texture = calloc(1, sizeof(texture));

  if (!texture) {
    stbi_image_free(texture->data);
  } else {
    texture->data = data;
    texture->width = width;
    texture->height = height;
  }

  return texture;
}

void
destroy_texture(texture_t* const texture)
{
  stbi_image_free(texture->data);
  free(texture);
}

color_t
sample_texture(const texture_t* const texture, float x, float y)
{
  // TODO Bounds check
  const size_t tx = texture->width * x;
  const size_t ty = texture->height * y;

  const size_t offset = num_components * (ty * texture->width + tx);
  const color_t* const color = (color_t*)(texture->data + offset);

  return *color;
}
