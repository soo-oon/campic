/******************************************************************************/
/*!
\file   BitmapFont.hpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Sprite.hpp"

class BitmapFont
{
public:
    struct Character
    {
        char id = char(-1);
        unsigned short x = 0;
        unsigned short y = 0;
        unsigned short width = 0;
        unsigned short height = 0;
        short xoffset = 0;
        short yoffset = 0;
        short xadvance = 0;
        unsigned char page = 0;
    };

    struct Information
    {
        short fontSize = 0;
        std::string fontName{};
        unsigned short lineHeight = 0;
        unsigned short imageWidth = 0;
        unsigned short imageHeight = 0;
        unsigned short pagesCount = 0;
        std::vector<std::string> pageNames{};
    };

public:
    bool LoadFromFile(const std::string& fnt_filepath);
    const Information& GetInformation() const;
    Character GetCharacter(char character_id) const;
    unsigned short GetLineHeight() const;
    const Sprite& GetSprite(int page_index) const;
    bool HasCharacter(char character_id) const;

private:
    bool CanParseFile(const std::string& fnt_filepath);

private:
    Information information{};
    std::unordered_map<char, Character>characters{};
    std::vector<Sprite> pageTextures{};
};
