#pragma once

#include <string>
#include "Input.hpp"
#include "Graphics.hpp"
#include <vector>
#include "Application.hpp"

const int TILE_SIZE = 48;
const int TEMP_WIDTH = 12800;
const int TEMP_HEIGHT = 10240;

enum class Tile_Type
{
    Physical,
    Graphical
};


class Tile_Map
{
public:
    bool Initialize();
    void Update(float dt);
	void RemoveTiles();

    std::unordered_map<int, Object*>& GetGraphicsTiles() { return graphics_tiles; }
    std::unordered_map<int, Object*>& GetPhysicalTiles() { return physical_tiles; }
    void Make_Tile(std::string image, Tile_Type type);
    void Make_Ani_Tile(std::string image, Tile_Type type);
    void Delete_Tile();
    void Delete_Ani_Tile();
    Object* GetSpecificTile(vector2 position);
    void SetReset(bool reset) { init = reset; }

    bool CheckTile(vector2 position)
    {

    }

    void InsertGraphicalTiles(int grid_, Object* tiles);
    void InsertPhysicalTiles(int grid_, Object* tiles);

private:
    void Normal_Tile(std::string& image, int x, int y, vector2 position, Tile_Type type);
    void Ani_Tile(std::string& image, int x, int y, vector2 position, Tile_Type type);

    std::unordered_map<int, Object*> graphics_tiles;
    std::unordered_map<int, Object*> physical_tiles;

    int m_number = 0;
    bool init = false;

    bool tile_grid[TEMP_WIDTH / TILE_SIZE][TEMP_HEIGHT / TILE_SIZE] = {false};
};

extern Tile_Map Tile_Map_;
extern Tile_Map Background_tiles_;
extern Tile_Map Foreground_tiles_;
