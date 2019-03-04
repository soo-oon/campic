#include "Tile_Map.hpp"
#include <iostream>
#include "Physics.hpp"

Tile_Map Tile_Map_;

void Tile_Map::Make_Tile(std::string image, Tile_Type type)
{
	int tile_x = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).x + TEMP_WIDTH / 2);
	int tile_y = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).y + TEMP_HEIGHT / 2);

    vector2 tile_position = {0};

    if (!tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE])
    {
        tile_position = { (float)((2 * (floor)(tile_x / TILE_SIZE) + 1)* TILE_SIZE / 2) - TEMP_WIDTH / 2
            , (float)((2 * (floor)(tile_y / TILE_SIZE) + 1)*TILE_SIZE) / 2 - TEMP_HEIGHT / 2 };
       
    	Normal_Tile(image, tile_x, tile_y, tile_position, type);
        
    	tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE] = true;
    }
}

void Tile_Map::Make_Ani_Tile(std::string image, Tile_Type type)
{
	int tile_x = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).x + TEMP_WIDTH / 2);
	int tile_y = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).y + TEMP_HEIGHT / 2);

	vector2 tile_position = { 0 };

	if (!tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE])
	{
		tile_position = { (float)((2 * (floor)(tile_x / TILE_SIZE) + 1)* TILE_SIZE / 2) - TEMP_WIDTH / 2
			, (float)((2 * (floor)(tile_y / TILE_SIZE) + 1)*TILE_SIZE) / 2 - TEMP_HEIGHT / 2 };
		
		Ani_Tile(image, tile_x, tile_y, tile_position, type);
		
		tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE] = true;
	}
}

void Tile_Map::Delete_Tile()
{
	int tile_x = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).x) + TEMP_WIDTH / 2;
	int tile_y = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).y) + TEMP_HEIGHT / 2;

    if (tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE])
    {
        graphics_tiles.erase((tile_x / TILE_SIZE *TEMP_WIDTH + tile_y / TILE_SIZE));
        tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE] = false;
    }
}

void Tile_Map::Delete_Ani_Tile()
{
	int tile_x = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).x) + TEMP_WIDTH / 2;
	int tile_y = static_cast<int>(Input::GetMousePos(Graphics_.camera_zoom).y) + TEMP_HEIGHT / 2;

	if (tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE])
	{
		graphics_tiles.erase((tile_x / TILE_SIZE * TEMP_WIDTH + tile_y / TILE_SIZE));
		tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE] = false;
	}
}

void Tile_Map::Normal_Tile(std::string& image, int x , int y, vector2 position, Tile_Type type)
{
	Object* tile = new Object();
	tile->SetTranslation({ position });
	tile->SetScale({ static_cast<float>(TILE_SIZE) });
	tile->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	tile->Add_Init_Component(new Sprite(image));

	if (type == Tile_Type::Physical)
	{
		physics_tiles.insert(std::pair<int, Object*>((x / TILE_SIZE * TEMP_WIDTH + y / TILE_SIZE), tile));
	}
	else
		graphics_tiles.insert(std::pair<int, Object*>((x / TILE_SIZE * TEMP_WIDTH + y / TILE_SIZE), tile));
}

void Tile_Map::Ani_Tile(std::string& image, int x, int y, vector2 position, Tile_Type type)
{
	Object* tile = new Object();
	std::string tile_name = "tile";
	tile_name += std::to_string(++m_number);
	tile->SetTranslation({ position });
	tile->SetScale({ static_cast<float>(TILE_SIZE) });
	tile->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
	tile->Add_Init_Component(new Animation(image, tile_name, 3, 0.1f, true));

	if (type == Tile_Type::Physical)
	{
		physics_tiles.insert(std::pair<int, Object*>((x / TILE_SIZE * TEMP_WIDTH + y / TILE_SIZE), tile));
	}
	else
		graphics_tiles.insert(std::pair<int, Object*>((x / TILE_SIZE * TEMP_WIDTH + y / TILE_SIZE), tile));

	std::cout << graphics_tiles.size() << std::endl;
}