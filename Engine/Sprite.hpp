/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Component.hpp"
#include <gl/glew.h>
#include <string>
#include "Color.hpp"

class Sprite : public Component
{
public:
	Sprite(const std::string& file_path_ = NULL)
		: path(file_path_), handle_to_texture(0)
	{
	}

    ~Sprite() = default;
    Sprite(const Sprite& other);
    Sprite& operator=(const Sprite& other);

    bool Initialize(Object* Ob) override;
    void Update(float dt) override;
    void Delete() override;

	bool IsFlip() { return flip; }
	void ChangeSprite(const std::string path_);
    bool Texture_Load();

	//************** Maybe Delete after optimizing Imgui
	void Flip_Not() { flip = false; }
	void Flip() { flip = true; }
	//**************

    void Bind(unsigned int slot = 0);
    void ScreenShot(const std::string& file_path) const;
    void UnLoadSprite();
    void DeleteSpriteTexture();

    int GetPixelsBufferBytesSize() const;

    int GetWidth() const { return width; }
    int GetHeigth() const { return height; }

	void Imgui_Sprite();

    GLuint GetTextureHandler() const { return handle_to_texture; }
private:
	bool flip = false;
    void LoadSprite();

	std::string path = NULL;
    GLuint handle_to_texture;
    int width = 0;
    int height = 0;
    static const int ChannelsPerColor = sizeof(Color::RGBA32);
    unsigned char* pixel;
};
