#pragma once

#include <string>
#include "Input.hpp"
#include "Graphics.hpp"

const int TILE_SIZE = 64;
const int TEMP_WIDTH = 1280;
const int TEMP_HEIGHT = 960;


class Tile_Map
{
public:

    void Make_Tile(std::string image);
    void Make_Object(std::string& image, vector2 position);
private:


    bool tile_grid_1[TEMP_WIDTH / TILE_SIZE / 2][TEMP_HEIGHT / TILE_SIZE / 2] = { false };
    bool tile_grid_2[TEMP_WIDTH / TILE_SIZE / 2][TEMP_HEIGHT / TILE_SIZE / 2] = { false };
    bool tile_grid_3[TEMP_WIDTH / TILE_SIZE / 2][TEMP_HEIGHT / TILE_SIZE / 2] = { false };
    bool tile_grid_4[TEMP_WIDTH / TILE_SIZE / 2][TEMP_HEIGHT / TILE_SIZE / 2] = { false };

};

extern Tile_Map tile_map_;