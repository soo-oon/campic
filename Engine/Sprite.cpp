#include "Sprite.hpp"
#include <SOIL.h>
#include <cassert>

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
    unsigned char* temp = SOIL_load_image(file_path.c_str(), &width, &height,
                                          nullptr, SOIL_LOAD_RGBA);

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
    SOIL_save_screenshot(file_path.c_str(), SOIL_SAVE_TYPE_BMP, 0, 0, width, height);
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
