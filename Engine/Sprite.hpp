#pragma once
#include "Component.hpp"
#include <gl/glew.h>
#include <string>
#include "Color.hpp"

class Sprite : public Component
{
public:
	Sprite() = default;
	~Sprite();
	Sprite(const Sprite& other);
	Sprite& operator=(const Sprite& other);

	// TODO**********************
	bool Initialize() override;
	void Update(float dt) override;
	void Delete() override;
	//******************************

	bool Texture_Load(const std::string& file_path);
	void LoadSprite();
	void Bind(unsigned int slot = 0);
	void ScreenShot(const std::string& file_path) const;
	void UnLoadSprite();
	void DeleteSpriteTexture();

	int GetPixelsBufferBytesSize() const;

	int GetWidth() const { return width; }
	int GetHeigth() const { return height; }

	GLuint GetTextureHandler() const { return handle_to_texture; }
private:
	unsigned char* piexel = nullptr;
	GLuint handle_to_texture = 0;
	int width = 0;
	int height = 0;
	static const int ChannelsPerColor = sizeof(Color::RGBA32);
};
