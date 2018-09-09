#include "Texture.hpp"
#include "Image.hpp"
#include <cassert>

bool Texture::LoadFromFile(const std::string & file_path)
{
    Image image;
    bool loaded = image.LoadFromPNG(file_path);

    return loaded && Generate(image);
}

bool Texture::Generate(const Image& image)
{
	width = image.GetWidth();
	height = image.GetHeigth();

	glGenTextures(1, &handle_to_texture);

	glBindTexture(GL_TEXTURE_2D, handle_to_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	const int base_mipmap_level = 0;
	const int zero_border = 0;

	glTexImage2D(GL_TEXTURE_2D, base_mipmap_level, GL_RGBA16, width, height,
		zero_border, GL_RGBA, GL_UNSIGNED_BYTE, image.GetpixelsPointer());

	return true;
}

void Texture::Bind(unsigned slot) const
{
    if (handle_to_texture == 0)
        return;

    assert(slot < 32);

    glActiveTexture(GL_TEXTURE0+slot);

    glBindTexture(GL_TEXTURE_2D, handle_to_texture);
}

Texture::Texture(const Texture& other)
    : handle_to_texture{ other.handle_to_texture }, width{ other.width }, height{ other.height }
{
}

Texture& Texture::operator=(const Texture& other)
{
    if (this == &other)
        return *this;

    handle_to_texture = other.handle_to_texture;
    width = other.width;
    height = other.height;
    return *this;
}