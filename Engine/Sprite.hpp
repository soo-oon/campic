#pragma once
#include "Component.hpp"
#include <gl/glew.h>
#include <string>
#include "Color.hpp"

class Sprite : public Component
{
public:
    Sprite() = default;
    ~Sprite() = default;
    Sprite(const Sprite& other);
    Sprite& operator=(const Sprite& other);

    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;

	bool IsFlip() { return flip; }

	//************** Maybe Delete after optimizing Imgui
	void Flip_Not() { flip = false; }
	void Flip() { flip = true; }
	//**************

    bool Texture_Load(const std::string& file_path);
    void Bind(unsigned int slot = 0);
    void ScreenShot(const std::string& file_path) const;
    void UnLoadSprite();
    void DeleteSpriteTexture();

    int GetPixelsBufferBytesSize() const;

    int GetWidth() const { return width; }
    int GetHeigth() const { return height; }

    GLuint GetTextureHandler() const { return handle_to_texture; }
private:
	bool flip = false;
    void LoadSprite();

    GLuint handle_to_texture;
    int width = 0;
    int height = 0;
    static const int ChannelsPerColor = sizeof(Color::RGBA32);
    unsigned char* pixel;
};
