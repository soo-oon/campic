#include "Sprite.hpp"
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#pragma warning(push)
#pragma warning(disable : 4505) // unreferenced local function has been removed
#pragma warning(disable : 4100) // unreferenced formal parameter
#include "stb_image.h"
#pragma warning(pop)

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "stb_image_write.h"

Sprite::Sprite(const Sprite& other)
    : handle_to_texture(other.handle_to_texture), width(other.width),
      height(other.height)
{
}

Sprite& Sprite::operator=(const Sprite& other)
{
    if (this == &other)
        return *this;

    handle_to_texture = other.handle_to_texture;
    width = other.width;
    height = other.height;

    return *this;
}

bool Sprite::Initialize(Object* Ob)
{
    type = sprite;
    piexel = nullptr;
    handle_to_texture = 0;

    return true;
}

void Sprite::Update(float /*dt*/)
{
}

void Sprite::Delete()
{
    UnLoadSprite();
}

bool Sprite::Texture_Load(const std::string& file_path)
{
    unsigned char* temp = stbi_load(file_path.c_str(), &width, &height,
                                          nullptr, STBI_rgb_alpha);

    if (temp == nullptr)
        return false;

    piexel = temp;

    LoadSprite();
    return true;
}

void Sprite::LoadSprite()
{
    glGenTextures(1, &handle_to_texture);

    glBindTexture(GL_TEXTURE_2D, handle_to_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    const int base_mipmap_level = 0;
    const int zero_border = 0;

    glTexImage2D(GL_TEXTURE_2D, base_mipmap_level, GL_RGBA16, width, height,
                 zero_border, GL_RGBA, GL_UNSIGNED_BYTE, piexel);
}

void Sprite::Bind(unsigned int slot)
{
    if (handle_to_texture == 0)
        return;

    assert(slot < 32);

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, handle_to_texture);
}

void Sprite::ScreenShot(const std::string& file_path) const
{
	if (!stbi_write_png(file_path.c_str(), width, height, STBI_rgb_alpha, piexel, width*ChannelsPerColor))
		return;
}

void Sprite::UnLoadSprite()
{
    DeleteSpriteTexture();
    piexel = nullptr;
}

void Sprite::DeleteSpriteTexture()
{
    if (handle_to_texture != 0)
    {
        glDeleteTextures(1, &handle_to_texture);
    }
    handle_to_texture = 0;
}

int Sprite::GetPixelsBufferBytesSize() const
{
    return ChannelsPerColor * sizeof(piexel);
}
