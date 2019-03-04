#pragma once

#include <string>
#include "Input.hpp"
#include "Graphics.hpp"
#include <vector>
#include "Application.hpp"

const int TILE_SIZE = 64;
const int TEMP_WIDTH = 12800;
const int TEMP_HEIGHT = 10240;

enum class Tile_Kind
{
    Physics,
    Graphics
};


class Tile_Map
{
public:
    std::unordered_map<int, Object*>& GetGraphicsTiles() { return graphics_tiles; }
    std::unordered_map<int, Object*>& GetPhysicsTiles() { return physics_tiles; }
    void Make_Tile(std::string image, Tile_Kind kind);
	void Make_Ani_Tile(std::string image, Tile_Kind kind);
    void Delete_Tile();
	void Delete_Ani_Tile();
private:
<<<<<<< HEAD
	void Make_Object(std::string& image, int x, int y, vector2 position, Tile_Kind kind);
	void Make_Ani_Object(std::string & image, int x, int y, vector2 position, Tile_Kind kind);
=======
	void Normal_Tile(std::string& image, int x, int y, vector2 position, Tile_Kind kind);
	void Ani_Tile(std::string& image, int x, int y, vector2 position, Tile_Kind kind);
>>>>>>> tw

    std::unordered_map<int, Object*> graphics_tiles;
    std::unordered_map<int, Object*> physics_tiles;

	int m_number = 0;

    bool tile_grid[TEMP_WIDTH / TILE_SIZE][TEMP_HEIGHT / TILE_SIZE] = { false };
    
};

extern Tile_Map Tile_Map_;
extern Tile_Map Background_tiles_;
extern Tile_Map Foreground_tiles_;
