/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: JSON.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Ji Hun Park
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "filewritestream.h"
#include "filereadstream.h"
#include "Objectmanager.hpp"
#include "prettywriter.h"
#include "StateManager.hpp"
#include "Tile_Map.hpp"
#include "State.hpp"
#include <map>

enum class Tile_Type;
using namespace rapidjson;

class JSON
{
public:
	bool Initialize();
	void Update(float /*dt*/);
	void Quit();

	//Player
	void PlayerToDoc(Object* obj);

	//Objects
	void ObjectsToDocument(Object* obj);
	void SaveObjectsToJson();
	void LoadObjectFromJson();
	Document LoadObjectDocumentFromJson();

	//Tiles
	void TilesToDocument(int grid_, Object * obj, Tile_Type type);
	void SaveTilesToJson(Tile_Type type);
	void LoadTilesFromJson(Tile_Type type);
	Document LoadTilesDocumentFromJson(Tile_Type type);

	//Helper class
	Value ComponentAnimation(Object* obj);
	Value ComponentTransform(Object* obj);
	Value ComponentStatus(Object* obj);
	Value ComponentCamera(Object* obj);
	Value ComponentSprite(Object* obj);
	Value ComponentCollision(Object* obj);
	Value ComponentParticle(Object* obj);
	Value ComponentSound(Object* obj);
	Value ComponentFont(Object* obj);

	Document& GetObjectDocument() { return ObjectDocument; }
	Document& GetTileDocument() { return TileDocument; }

private:
	Document ObjectDocument;
	Document TileDocument;

	StringBuffer ObjectBuffer;
	StringBuffer TileBuffer;

	std::string file_path = "asset/JsonFiles/";

};

extern JSON JSON_;