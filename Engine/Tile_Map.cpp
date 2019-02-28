#include "Tile_Map.hpp"
#include <iostream>

Tile_Map Tile_Map_;

void Tile_Map::Make_Tile(std::string image)
{
    int tile_x = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).x);
    int tile_y = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).y);

    vector2 tile_position = {0};
    std::cout << tile_x << ", " << tile_y << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    //quadrant 1 
    if(tile_x > 0 && tile_y > 0 )
    {
        if (!tile_grid_1[tile_x / TILE_SIZE][tile_y / TILE_SIZE])
        {
            std::cout << tile_x/TILE_SIZE << std::endl;
            tile_position = { (float)((2 * (floor)(tile_x / (float)TILE_SIZE) + 1 )* TILE_SIZE / 2), (float)((2 * (floor)((float)tile_y / (float)TILE_SIZE) + 1)*TILE_SIZE) / 2 };
            Make_Object(image, tile_position);
            tile_grid_1[tile_x / TILE_SIZE][tile_y / TILE_SIZE] = true;
        }
    }
    //quadrant 2
    else if(tile_x < 0 && tile_y > 0)
    {
        if (!tile_grid_2[std::abs(tile_x / TILE_SIZE)][std::abs(tile_y / TILE_SIZE)])
        {
            tile_position = { (float)((2 * (ceil)((float)tile_x / (float)TILE_SIZE) - 1)* TILE_SIZE / 2), (float)((2 * (floor)((float)tile_y / (float)TILE_SIZE) + 1) *TILE_SIZE) / 2 };
            std::cout << tile_position.x << ", " << tile_position.y << std::endl;
            Make_Object(image, tile_position);
            tile_grid_2[std::abs(tile_x / TILE_SIZE)][std::abs(tile_y / TILE_SIZE)] = true;
        }
    }
    //quadrant 3 
    else if (tile_x < 0 && tile_y < 0)
    {
        if (!tile_grid_3[std::abs(tile_x / TILE_SIZE)][std::abs(tile_y / TILE_SIZE)])
        {
            std::cout << std::abs(tile_y / TILE_SIZE) << std::endl;
            tile_position = { (float)((2 * (ceil)((float)tile_x / (float)TILE_SIZE) - 1)* TILE_SIZE / 2), (float)((2 * (ceil)((float)tile_y / (float)TILE_SIZE) - 1) *TILE_SIZE) / 2 };
            std::cout << tile_position.x << ", " << tile_position.y << std::endl;
            Make_Object(image, tile_position);
            tile_grid_3[std::abs(tile_x / TILE_SIZE)][std::abs(tile_y / TILE_SIZE)] = true;
        }
    }
    //quadrant 4 
    else if (tile_x > 0 && tile_y < 0)
    {
        if (!tile_grid_4[std::abs(tile_x / TILE_SIZE)][std::abs(tile_y / TILE_SIZE)])
        {
            tile_position = { (float)((2 * (floor)(tile_x / (float)TILE_SIZE) + 1)* TILE_SIZE / 2), (float)((2 * (ceil)((float)tile_y / (float)TILE_SIZE) - 1) *TILE_SIZE) / 2 };
            std::cout << tile_position.x << ", " << tile_position.y << std::endl;
            Make_Object(image, tile_position);
            tile_grid_4[std::abs(tile_x / TILE_SIZE)][std::abs(tile_y / TILE_SIZE)] = true;
        }
    }

}

void Tile_Map::Make_Object(std::string& image, vector2 position)
{
    Object* tile = new Object();
    tile->SetTranslation({ position });
    tile->SetScale({ static_cast<float>(TILE_SIZE) });
    tile->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
    tile->AddComponent(new Sprite(image));
    Objectmanager_.AddObject(tile);
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
