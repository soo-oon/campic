#pragma once

#include "Image.hpp"
#include <cassert>
#include <SOIL.h>

void Image::ResizeWidthHeight(int pixel_width, int pixel_height)
{
    assert(pixel_width >= 0 && pixel_height >= 0);

    width = pixel_width;
    height = pixel_height;
}

bool Image::LoadFromPNG(const std::string& file_path)
{
    unsigned char* temp= SOIL_load_image(file_path.c_str(), &width, &height,
        0, SOIL_LOAD_RGBA);

    if (temp == nullptr)
        return false;

	ResizeWidthHeight(width, height);

	pixel = temp;

    return true;
}

void Image::SaveToPNG(const std::string& file_path) const
{
	SOIL_save_screenshot(file_path.c_str(), SOIL_SAVE_TYPE_BMP, 0,0,width, height);
}


int Image::GetWidth() const
{
    return width;
}

int Image::GetHeigth() const
{
    return height;
}

unsigned char* Image::GetpixelsPointer()
{
	return pixel;
}

const unsigned char* Image::GetpixelsPointer() const
{
	return pixel;
}

int Image::GetPixelsBufferBytesSize() const
{
    return ChannelsPerColor * sizeof(pixel);
}
