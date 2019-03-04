#include "Tile_Map.hpp"
#include <iostream>
#include "Physics.hpp"

Tile_Map Tile_Map_;

void Tile_Map::Make_Tile(std::string image, Tile_Kind kind)
{
    int tile_x = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).x + TEMP_WIDTH/2);
    int tile_y = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).y + TEMP_HEIGHT/2);

    vector2 tile_position = {0};

    std::cout << tile_x / TILE_SIZE << ", " << tile_y / TILE_SIZE << std::endl;
    std::cout << "****************************************" << std::endl;

    if (!tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE])
    {
        std::cout << "false" << std::endl;
        tile_position = { (float)((2 * (floor)(tile_x / TILE_SIZE) + 1)* TILE_SIZE / 2) - TEMP_WIDTH / 2
            , (float)((2 * (floor)(tile_y / TILE_SIZE) + 1)*TILE_SIZE) / 2 - TEMP_HEIGHT / 2 };
        std::cout << tile_position.x << ", " << tile_position.y << std::endl;
        Make_Object(image,tile_x,tile_y, tile_position, kind);
        tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE] = true;
    }
}


void Tile_Map::Delete_Tile()
{
    int tile_x = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).x) + TEMP_WIDTH / 2;
    int tile_y = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).y) + TEMP_HEIGHT/2;

    if (tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE])
    {
        graphics_tiles.erase((tile_x / TILE_SIZE *TEMP_WIDTH + tile_y / TILE_SIZE));
        tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE] = false;
    }

}

void Tile_Map::Make_Object(std::string& image,int x , int y, vector2 position, Tile_Kind kind)
{
    Object* tile = new Object();
    tile->SetTranslation({ position });
    tile->SetScale({ static_cast<float>(TILE_SIZE) });
    tile->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
    tile->Add_Init_Component(new Sprite(image));
    
    if (kind == Tile_Kind::Physics)
    {
        physics_tiles.insert(std::pair<int, Object*>((x / TILE_SIZE * TEMP_WIDTH + y / TILE_SIZE), tile));
    }
    else
        graphics_tiles.insert(std::pair<int, Object*>((x / TILE_SIZE *TEMP_WIDTH + y / TILE_SIZE) , tile));
}

void Tile_Map::Make_Ani_Object(std::string & image, vector2 position)
{
	Object* tile = new Object();
	tile->SetTranslation({ position });
	tile->SetScale({ static_cast<float>(TILE_SIZE) });
	tile->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	tile->AddComponent(new Sprite(image));
	Objectmanager_.AddObject(tile);
}
