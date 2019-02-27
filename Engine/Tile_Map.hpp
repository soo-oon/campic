#pragma once

#include <string>
#include "Input.hpp"
#include "Graphics.hpp"
#include <vector>
#include "Application.hpp"

const int TILE_SIZE = 64;
const int TEMP_WIDTH = 12800;
const int TEMP_HEIGHT = 10240;


class Tile_Map
{
public:
    std::vector<std::unique_ptr<Object>>& GetTileObjectes() { return tile_Object; }
    void Make_Tile(std::string image);
private:
	void Make_Object(std::string& image, vector2 position);
	void Make_Ani_Object(std::string& image, vector2 position);

    std::vector<std::unique_ptr<Object>> tile_Object;

    bool tile_grid_1[TEMP_WIDTH / TILE_SIZE / 2][TEMP_HEIGHT / TILE_SIZE / 2] = { false };
    bool tile_grid_2[TEMP_WIDTH / TILE_SIZE / 2][TEMP_HEIGHT / TILE_SIZE / 2] = { false };
    bool tile_grid_3[TEMP_WIDTH / TILE_SIZE / 2][TEMP_HEIGHT / TILE_SIZE / 2] = { false };
    bool tile_grid_4[TEMP_WIDTH / TILE_SIZE / 2][TEMP_HEIGHT / TILE_SIZE / 2] = { false };

};

extern Tile_Map Tile_Map_;