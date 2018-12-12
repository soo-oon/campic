#pragma once
#include "State.hpp"
#include "Objectmanager.hpp"
#include "Object.hpp"
#include "JSON.hpp"

#define no_texture		"no_texture";
#define card_heart		"asset/images/heart.png";
#define card_diamond	"asset/images/dia.png";
#define dr_strange_dot	"asset/images/Dr_Strange.png";
#define wall_			"asset/images/wall.png";
#define road			"asset/images/Road.png";


class MapEditorTest : public State
{
public:
	void Initialize() override;
	void Update(float dt) override;
	void ShutDown() override;

	void LoadMap();

private:
	size_t object_count = 1;
	std::string object_name = "object";

	std::map<std::string, Object> objects_and_names;
	std::map<std::string, Object>* pt_object_map = &objects_and_names;

	Object* newObject;
	Object* selected_object = nullptr;
};