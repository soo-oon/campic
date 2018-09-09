#pragma once

#include <GL\glew.h>
#include <string>

class Image;

class Texture
{
public:
    Texture() = default;

    bool LoadFromFile(const std::string& file_path);

    bool Generate(const Image& image);

    void Bind(unsigned int slot = 0) const;

    GLuint GetTextureHandler() const { return handle_to_texture; }

    Texture(const Texture& other);
    Texture& operator=(const Texture& other);

private:
    GLuint handle_to_texture;
    int width = 0;
    int height = 0;
};