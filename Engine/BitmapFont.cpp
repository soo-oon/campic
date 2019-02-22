/******************************************************************************/
/*!
\file   BitmapFont.cpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/
#include "BitmapFont.hpp"
#include <cassert>
#include <filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

namespace
{
    template <typename Number>
    void SearchLineAndSetNumber(const std::string& line, const std::string& key, Number& storage);
    void SearchLineAndSetString(const std::string& line, std::string key, std::string& storage);
}


bool BitmapFont::LoadFromFile(const std::string& fnt_filepath)
{
    if (!CanParseFile(fnt_filepath))
        return false;

    pageTextures.reserve(information.pagesCount);

    const auto file_dir = fs::path(fnt_filepath).parent_path();

    for(const auto& page_name : information.pageNames)
    {
        const auto image_filepath = file_dir / page_name;

        if (!fs::exists(image_filepath))
            return false;

        pageTextures.emplace_back();

        const auto loaded = pageTextures.back().FontTexture_Load(image_filepath.string());

        if (!loaded)
            return false;
    }

    return true;
}

const BitmapFont::Information& BitmapFont::GetInformation() const
{
    return information;
}

BitmapFont::Character BitmapFont::GetCharacter(char character_id) const
{
    auto match = characters.find(character_id);

    if(match == characters.end())
    {
        match = characters.find((char)-1);

        if (match == characters.end())
            return BitmapFont::Character{};
    }
    return match->second;
}

unsigned short BitmapFont::GetLineHeight() const
{
    return information.lineHeight;
}

const Sprite& BitmapFont::GetSprite(int page_index) const
{
    assert(information.pagesCount > 0);
    assert(page_index >= 0 && page_index < information.pagesCount);

    return pageTextures.at(page_index);
}

bool BitmapFont::HasCharacter(char character_id) const
{
    auto match = characters.find(character_id);
    return match != characters.end();
}

bool BitmapFont::CanParseFile(const std::string& fnt_filepath)
{
    std::ifstream stream(fnt_filepath);
    if (!stream)
        return false;

    std::string line;
    std::string line_type;
    while(stream)
    {
        stream >> line_type;
        std::getline(stream, line);

        if(line_type == "info")
        {
            SearchLineAndSetString(line, "face", information.fontName);
            SearchLineAndSetNumber(line, "size", information.fontSize);
        }
        else if(line_type == "common")
        {
            SearchLineAndSetNumber(line, "lineHeight", information.lineHeight);
            SearchLineAndSetNumber(line, "scaleW", information.imageWidth);
            SearchLineAndSetNumber(line, "scaleH", information.imageHeight);
            SearchLineAndSetNumber(line, "pages", information.pagesCount);

            information.pageNames.resize(information.pagesCount);
        }
        else if(line_type=="page")
        {
            int offset = 0;
            std::string name{};
            SearchLineAndSetNumber(line, "id", offset);
            SearchLineAndSetString(line, "file", name);

            information.pageNames.at(offset) = name;
        }
        else if(line_type == "char")
        {
            Character desc{};

            SearchLineAndSetNumber(line, "id", desc.id);
            SearchLineAndSetNumber(line, "x", desc.x);
            SearchLineAndSetNumber(line, "y", desc.y);
            SearchLineAndSetNumber(line, "width", desc.width);
            SearchLineAndSetNumber(line, "height", desc.height);
            SearchLineAndSetNumber(line, "xoffset", desc.xoffset);
            SearchLineAndSetNumber(line, "yoffset", desc.yoffset);
            SearchLineAndSetNumber(line, "xadvance", desc.xadvance);
            SearchLineAndSetNumber(line, "page", desc.page);

            characters.insert_or_assign(desc.id, desc);
        }
    }
    return true;
}

namespace
{
    template <typename Number>
    void SearchLineAndSetNumber(const std::string& line, const std::string& key, Number& storage)
    {
        std::string temp = key;
        temp += "=";

        auto offset = line.find(temp);
        if (offset != std::string::npos)
        {
            offset += temp.length();
            auto end = line.find(" ", offset);
            int mystoi = std::stoi(line.substr(offset, end - offset));
            storage = static_cast<Number>(mystoi);
        }
    }

    void SearchLineAndSetString(const std::string& line, std::string key, std::string& storage)
    {
        key += "=\"";
        auto offset = line.find(key);

        if (offset != std::wstring::npos)
        {
            offset += key.length();
            auto end = line.find("\"", offset);
            storage = line.substr(offset, end - offset);
        }
    }
}