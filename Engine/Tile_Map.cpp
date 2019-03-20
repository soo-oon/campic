#include "Tile_Map.hpp"
#include <iostream>
#include "Physics.hpp"

Tile_Map Tile_Map_;


bool Tile_Map::Initialize()
{
    if (!graphics_tiles.empty())
    {
        for (auto& obj : graphics_tiles)
        {
            for (auto& component : obj.second->GetComponent())
            {
                component->Initialize(obj.second);
            }
        }
    }
    return true;
}

void Tile_Map::Update(float dt)
{
    if(!init)
    {
        Initialize();
        init = true;
    }
	for(auto it = graphics_tiles.begin(); it != graphics_tiles.end(); ++it)
	{
		for(auto component : it->second->GetComponent())
		{
			component->Update(dt);
		}
	}
}

void Tile_Map::Make_Tile(std::string image, Tile_Type type)
{
	int tile_x = static_cast<int>(Input::GetMousePos().x + TEMP_WIDTH / 2);
	int tile_y = static_cast<int>(Input::GetMousePos().y + TEMP_HEIGHT / 2);

    vector2 tile_position = {0};

    if (!tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE])
    {
        tile_position = { (float)((2 * (floor)(tile_x / TILE_SIZE) + 1)* TILE_SIZE / 2) - TEMP_WIDTH / 2
            , (float)((2 * (floor)(tile_y / TILE_SIZE) + 1)*TILE_SIZE) / 2 - TEMP_HEIGHT / 2 };
        std::cout << tile_position.x << ", " << tile_position.y << std::endl;
       
    	Normal_Tile(image, tile_x, tile_y, tile_position, type);
        
    	tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE] = true;
    }
}

void Tile_Map::Make_Ani_Tile(std::string image, Tile_Type type)
{
	int tile_x = static_cast<int>(Input::GetMousePos().x + TEMP_WIDTH / 2);
	int tile_y = static_cast<int>(Input::GetMousePos().y + TEMP_HEIGHT / 2);

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
	int tile_x = static_cast<int>(Input::GetMousePos().x) + TEMP_WIDTH / 2;
	int tile_y = static_cast<int>(Input::GetMousePos().y) + TEMP_HEIGHT / 2;

    if (tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE])
    {
        graphics_tiles.erase((tile_x / TILE_SIZE *TEMP_WIDTH + tile_y / TILE_SIZE));
        tile_grid[tile_x / TILE_SIZE][tile_y / TILE_SIZE] = false;
    }
}

void Tile_Map::Delete_Ani_Tile()
{
	int tile_x = static_cast<int>(Input::GetMousePos().x) + TEMP_WIDTH / 2;
	int tile_y = static_cast<int>(Input::GetMousePos().y) + TEMP_HEIGHT / 2;

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
	tile->AddInitComponent(new Sprite(image));
        tile->AddInitComponent(new Collision(box_));

	if (type == Tile_Type::Physical)
	{
		physical_tiles.insert(std::pair<int, Object*>((x / TILE_SIZE * TEMP_WIDTH + y / TILE_SIZE), tile));
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
	tile->AddInitComponent(new Animation(image, tile_name, 3, 0.1f, true));

	if (type == Tile_Type::Physical)
	{
		physical_tiles.insert(std::pair<int, Object*>((x / TILE_SIZE * TEMP_WIDTH + y / TILE_SIZE), tile));
	}
	else
		graphics_tiles.insert(std::pair<int, Object*>((x / TILE_SIZE * TEMP_WIDTH + y / TILE_SIZE), tile));

	std::cout << graphics_tiles.size() << std::endl;
}

void Tile_Map::InsertGraphicalTiles(int grid_, Object * tiles)
{
	graphics_tiles.insert(std::pair<int, Object*>(grid_, tiles));
}

void Tile_Map::InsertPhysicalTiles(int grid_, Object * tiles)
{
	physical_tiles.insert(std::pair<int, Object*>(grid_, tiles));
}


Object * Tile_Map::GetSpecificTile(vector2 position)
{
    int tile_position_x = static_cast<int>(position.x) + TEMP_WIDTH / 2;
    int tile_position_y = static_cast<int>(position.y) + TEMP_HEIGHT / 2;
    if (!graphics_tiles.empty())
    {
        if (graphics_tiles.find(tile_position_x / TILE_SIZE * TEMP_WIDTH + tile_position_y / TILE_SIZE) == graphics_tiles.end())
            return nullptr;
        else
            return graphics_tiles.at(tile_position_x / TILE_SIZE * TEMP_WIDTH + tile_position_y / TILE_SIZE);
    }
    return nullptr;
}
