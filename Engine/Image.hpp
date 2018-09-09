#include "Color.hpp"
#include <vector>

class Image
{
public:
    void ResizeWidthHeight(int pixel_width, int pixel_height);
    bool LoadFromPNG(const std::string& file_path);
	void SaveToPNG(const std::string& file_path)const;

    int GetWidth() const;
    int GetHeigth() const;


	unsigned char* GetpixelsPointer();
	const unsigned char* GetpixelsPointer() const;

    int GetPixelsBufferBytesSize() const;

private:
	unsigned char* pixel;
    int width = 0;
    int height = 0;
    static const int ChannelsPerColor = sizeof(Color::RGBA32);
};