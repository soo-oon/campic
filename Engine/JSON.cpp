#include "JSON.hpp"
#include "Status.hpp"
#include <iostream>

JSON JSON_;

bool JSON::Initialize()
{
	ObjectDocument.SetObject();
	//levels.SetObject();
	//if (!levels.IsObject())
	//	return false;
	//LoadLevelDocument();

	return true;
}

void JSON::Update(float dt)
{
}

void JSON::Quit()
{
	//SaveAtEnd();
	//SaveDocument();

	//for (std::map< std::string, std::unique_ptr<rapidjson::Document>>::iterator
	//	it = LevelDocuments.begin(); it != LevelDocuments.end(); it++)
	//	delete(it->second.get());
}

void JSON::ObjectsToDocument(Object* obj)
{
	//Trees for object info
	Value objTree(kArrayType);

	//Status info
	Value objStatusTree(kArrayType);
	Value objTransformTree(kArrayType);
	Value objSpriteTree(kArrayType);
	Value objAnimationTree(kArrayType);
	Value objCameraTree(kArrayType);

	//TODO
	//Collision info
	//Value objCollisionTree(kArrayType);
	//Particle info
	//Value objParticleTree(kArrayType);
	//RigidBody info
	//Value objRigidBodyTree(kArrayType);

	objTree.SetObject();
	objTransformTree.SetObject();
	objAnimationTree.SetObject();
	objCameraTree.SetObject();
	objStatusTree.SetObject();
	objSpriteTree.SetObject();

	objTransformTree = ComponentTransform(obj);
	if(obj->GetComponentByTemplate<Status>() != nullptr)
		objStatusTree = ComponentStatus(obj);
	if(obj->GetComponentByTemplate<Animation>() != nullptr)
		objAnimationTree = ComponentAnimation(obj);
	if(obj->GetComponentByTemplate<Camera>() != nullptr)
		objCameraTree = ComponentCamera(obj);
	if (obj->GetComponentByTemplate<Sprite>() != nullptr)
		objCameraTree = ComponentSprite(obj);

	objTree.AddMember("Status", objStatusTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Transform", objTransformTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Sprite", objSpriteTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Animation", objAnimationTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Camera", objCameraTree, ObjectDocument.GetAllocator());

	ObjectDocument.AddMember("Object", objTree, ObjectDocument.GetAllocator());

	ObjectDocument.Parse(ObjectBuffer.GetString());

	SaveObjectsToJson();
}

Value JSON::ComponentAnimation(Object* obj)
{
	Value objAnimationTree(kArrayType);
	Value objAnimationMap(kArrayType);
	Value current_animation, previous_animation, is_done, frame_time;
	std::vector<Value*> animation_string;
	std::vector<Value*> animation_map;

	//Animation_Information class
	//TODO Sprite
	Value c_is_repeats, c_previous_current_coordinate;
	Value p_is_repeats, p_previous_current_coordinate;

	objAnimationTree.SetObject();
	objAnimationMap.SetObject();
	current_animation.SetObject();
	previous_animation.SetObject();
	is_done.SetObject();
	frame_time.SetObject();
	c_is_repeats.SetObject();
	c_previous_current_coordinate.SetObject();
	p_is_repeats.SetObject();
	p_previous_current_coordinate.SetObject();

	auto animation_info = obj->GetComponentByTemplate<Animation>();
	auto current_animation_info = obj->GetComponentByTemplate<Animation>()->GetCurrentAnimation();
	auto previous_animation_info = obj->GetComponentByTemplate<Animation>()->GetPreviousAnimation();

	c_is_repeats.SetBool(current_animation_info.is_repeats);
	c_previous_current_coordinate.AddMember("x", current_animation_info.previous_current_coordinate.x, ObjectDocument.GetAllocator());
	c_previous_current_coordinate.AddMember("y", current_animation_info.previous_current_coordinate.y, ObjectDocument.GetAllocator());
	current_animation.AddMember("image_frames", current_animation_info.image_frames, ObjectDocument.GetAllocator());
	current_animation.AddMember("update_frames", current_animation_info.update_frames, ObjectDocument.GetAllocator());
	current_animation.AddMember("frame_per_seconds", current_animation_info.frame_per_seconds, ObjectDocument.GetAllocator());
	current_animation.AddMember("is_repeats", c_is_repeats, ObjectDocument.GetAllocator());
	current_animation.AddMember("previous_current_coordinate", c_previous_current_coordinate, ObjectDocument.GetAllocator());

	p_is_repeats.SetBool(previous_animation_info.is_repeats);
	p_previous_current_coordinate.AddMember("x", previous_animation_info.previous_current_coordinate.x, ObjectDocument.GetAllocator());
	p_previous_current_coordinate.AddMember("y", previous_animation_info.previous_current_coordinate.y, ObjectDocument.GetAllocator());
	previous_animation.AddMember("image_frames", previous_animation_info.image_frames, ObjectDocument.GetAllocator());
	previous_animation.AddMember("update_frames", previous_animation_info.update_frames, ObjectDocument.GetAllocator());
	previous_animation.AddMember("frame_per_seconds", previous_animation_info.frame_per_seconds, ObjectDocument.GetAllocator());
	previous_animation.AddMember("is_repeats", p_is_repeats, ObjectDocument.GetAllocator());
	previous_animation.AddMember("previous_current_coordinate", p_previous_current_coordinate, ObjectDocument.GetAllocator());

	is_done.SetBool(animation_info->IsDone());
	frame_time.SetFloat(animation_info->GetFrameTime());

	for (auto& temp : animation_info->GetAnimationMap())
	{
		int i = 0;
		Value animation_path;
		Value animation_info_;
		Value animation_is_repeats;
		Value animation_pc_coordinate;

		animation_path.SetObject();
		animation_info_.SetObject();
		animation_is_repeats.SetObject();
		animation_pc_coordinate.SetObject();

		animation_path.SetString(temp.first.c_str(), ObjectDocument.GetAllocator());
		animation_is_repeats.SetBool(temp.second.is_repeats);
		animation_pc_coordinate.AddMember("x", temp.second.previous_current_coordinate.x, ObjectDocument.GetAllocator());
		animation_pc_coordinate.AddMember("y", temp.second.previous_current_coordinate.y, ObjectDocument.GetAllocator());

		animation_info_.AddMember("image_frames", temp.second.image_frames, ObjectDocument.GetAllocator());
		animation_info_.AddMember("update_frames", temp.second.update_frames, ObjectDocument.GetAllocator());
		animation_info_.AddMember("frame_per_seconds", temp.second.frame_per_seconds, ObjectDocument.GetAllocator());
		animation_info_.AddMember("is_repeats", animation_is_repeats, ObjectDocument.GetAllocator());
		animation_info_.AddMember("previous_current_coordinate", animation_pc_coordinate, ObjectDocument.GetAllocator());

		animation_string.push_back(&animation_path);
		animation_map.push_back(&animation_info_);

		objAnimationMap.AddMember("path", *animation_string.at(i), ObjectDocument.GetAllocator());
		objAnimationMap.AddMember("info", *animation_map.at(i), ObjectDocument.GetAllocator());
		++i;
	}

	objAnimationTree.AddMember("current_animation", current_animation, ObjectDocument.GetAllocator());
	objAnimationTree.AddMember("previous_animation", previous_animation, ObjectDocument.GetAllocator());
	objAnimationTree.AddMember("map", objAnimationMap, ObjectDocument.GetAllocator());
	objAnimationTree.AddMember("is_done", is_done, ObjectDocument.GetAllocator());
	objAnimationTree.AddMember("frame_time", frame_time, ObjectDocument.GetAllocator());

	return objAnimationTree;
}

Value JSON::ComponentTransform(Object * obj)
{
	Value objTransformTree(kArrayType);
	Value pos, scale, rotation;

	objTransformTree.SetObject();
	pos.SetObject();
	scale.SetObject();
	rotation.SetObject();

	pos.AddMember("x", obj->GetTransform().GetTranslation().x, ObjectDocument.GetAllocator());
	pos.AddMember("y", obj->GetTransform().GetTranslation().y, ObjectDocument.GetAllocator());

	scale.AddMember("x", obj->GetTransform().GetScale().x, ObjectDocument.GetAllocator());
	scale.AddMember("y", obj->GetTransform().GetScale().y, ObjectDocument.GetAllocator());

	rotation.SetFloat(obj->GetTransform().GetRotation());

	objTransformTree.AddMember("position", pos, ObjectDocument.GetAllocator());
	objTransformTree.AddMember("scale", scale, ObjectDocument.GetAllocator());
	objTransformTree.AddMember("rotation", rotation, ObjectDocument.GetAllocator());

	return objTransformTree;
}

Value JSON::ComponentStatus(Object * obj)
{
	Value objStatusTree(kArrayType);
	Value objType, objTypeString, objTypeVal, isAlive;

	objStatusTree.SetObject();
	objType.SetObject();
	objTypeString.SetObject();
	objTypeVal.SetObject();
	isAlive.SetObject();

	auto type = obj->GetComponentByTemplate<Status>()->GetObjectType();

	switch (type)
	{
		case ObjectType::Player:
		{
			objTypeVal.SetInt(0);
			objTypeString.SetString("Player");
			break;
		}
		case ObjectType::Sword:
		{
			objTypeVal.SetInt(1);
			objTypeString.SetString("Sword");
			break;
		}
		case ObjectType::Enemy:
		{
			objTypeVal.SetInt(2);
			objTypeString.SetString("Enemy");
			break;
		}
		case ObjectType::Boss:
		{
			objTypeVal.SetInt(3);
			objTypeString.SetString("Boss");
			break;
		}
		case ObjectType::Wall:
		{
			objTypeVal.SetInt(4);
			objTypeString.SetString("Door");
			break;
		}
		case ObjectType::Door:
		{
			objTypeVal.SetInt(5);
			objTypeString.SetString("Door");
			break;
		}
		case ObjectType::Item:
		{
			objTypeVal.SetInt(6);
			objTypeString.SetString("Item");
			break;
		}
		case ObjectType::Shooting:
		{
			objTypeVal.SetInt(7);
			objTypeString.SetString("Shooting");
			break;
		}
		case ObjectType::None:
		{
			objTypeVal.SetInt(8);
			objTypeString.SetString("None");
			break;
		}
		default:
			break;
	}

	objType.AddMember("Value", objTypeVal, ObjectDocument.GetAllocator());
	objType.AddMember("Enum", objTypeString, ObjectDocument.GetAllocator());

	auto obj_info = obj->GetComponentByTemplate<Status>();

	isAlive.SetBool(obj_info->IsAlive());

	objStatusTree.AddMember("Type", objType, ObjectDocument.GetAllocator());
	objStatusTree.AddMember("HP", obj_info->GetHp(), ObjectDocument.GetAllocator());
	objStatusTree.AddMember("Damage", obj_info->GetDamage(), ObjectDocument.GetAllocator());
	objStatusTree.AddMember("Speed", obj_info->GetSpeed(), ObjectDocument.GetAllocator());
	objStatusTree.AddMember("isAlive", obj_info->IsAlive(), ObjectDocument.GetAllocator());

	return objStatusTree;
}

Value JSON::ComponentCamera(Object* obj)
{
	Value objCameraTree(kArrayType);
	Value center, up, right;

	objCameraTree.SetObject();
	center.SetObject();
	up.SetObject();
	right.SetObject();

	auto obj_info = obj->GetComponentByTemplate<Camera>();

	center.AddMember("x", obj_info->GetCenter().x, ObjectDocument.GetAllocator());
	center.AddMember("y", obj_info->GetCenter().y, ObjectDocument.GetAllocator());
	up.AddMember("x", obj_info->GetUp().x, ObjectDocument.GetAllocator());
	up.AddMember("y", obj_info->GetUp().y, ObjectDocument.GetAllocator());
	right.AddMember("x", obj_info->GetRight().x, ObjectDocument.GetAllocator());
	right.AddMember("y", obj_info->GetRight().y, ObjectDocument.GetAllocator());

	objCameraTree.AddMember("zoom", obj_info->GetZoomValue(), ObjectDocument.GetAllocator());
	objCameraTree.AddMember("center", center, ObjectDocument.GetAllocator());
	objCameraTree.AddMember("up", up, ObjectDocument.GetAllocator());
	objCameraTree.AddMember("right", right, ObjectDocument.GetAllocator());

	return objCameraTree;
}

Value JSON::ComponentSprite(Object* obj)
{
	Value objSpriteTree(kArrayType);
	std::string path;

	objSpriteTree.SetObject();

	auto obj_info = obj->GetComponentByTemplate<Sprite>();

	objSpriteTree.AddMember("is_flip", obj_info->IsFlip(), ObjectDocument.GetAllocator());
	objSpriteTree.AddMember("image_path", obj_info->GetPath(), ObjectDocument.GetAllocator());

	return objSpriteTree;
}

void JSON::SaveObjectsToJson()
{
	std::string filename(file_path);
	filename.append("Objects.json");

	FILE* fp = fopen(filename.c_str(), "w+");
		
	char writeBuffer[65535];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	PrettyWriter<FileWriteStream> writer(os);
	ObjectDocument.Accept(writer);
	
	fclose(fp);
}

Document JSON::LoadObjectDocumentFromJson()
{
	std::string filename(file_path);
	filename.append("Objects.json");

	FILE* fp = fopen(filename.c_str(), "r+");

	char readBuffer[65535];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document object_lists;
	object_lists.ParseStream(is);

	fclose(fp);

	return object_lists;
}

void JSON::LoadObjectFromJson()
{
	ObjectDocument = LoadObjectDocumentFromJson();

	for(auto& temp : ObjectDocument.GetObject())
	{
		Value& obj_array = temp.value;

		Value status, transform, animation, sprite;
		Object obj;

		status.SetObject();
		transform.SetObject();
		sprite.SetObject();
		animation.SetObject();

		status = obj_array.FindMember("Status")->value;
		transform = obj_array.FindMember("Transform")->value;
		sprite = obj_array.FindMember("Sprite")->value;
		animation = obj_array.FindMember("Animation")->value;

		// status
		int obj_type = status.FindMember("Type")->value.FindMember("Value")->value.GetInt();
		int hp_ = status.FindMember("HP")->value.GetInt();
		int attack_damage = status.FindMember("Damage")->value.GetInt();
		float speed = status.FindMember("Speed")->value.GetFloat();
		bool is_alive = status.FindMember("isAlive")->value.GetBool();
	
		obj.AddComponent(new Status(static_cast<ObjectType>(obj_type), hp_, attack_damage,speed,is_alive));

		//transform
		vector2 pos, scale;
		float rotation;

		pos.x = transform.FindMember("position")->value.FindMember("x")->value.GetFloat();
		pos.y = transform.FindMember("position")->value.FindMember("y")->value.GetFloat();
		scale.x = transform.FindMember("scale")->value.FindMember("x")->value.GetFloat();
		scale.y = transform.FindMember("scale")->value.FindMember("y")->value.GetFloat();
		rotation = transform.FindMember("rotation")->value.GetFloat();

		obj.SetTranslation(pos);
		obj.SetScale(scale);
		obj.SetRotation(rotation);

		//Sprite
		bool is_flip = false;
		std::string path;

		//is_flip = sprite.FindMember("is_flip")->value;

		//obj.AddComponent(new Sprite());
		//obj.GetComponentByTemplate<Sprite>()->Texture_Load("asset/images/Dr_Strange.png");

		obj.SetMesh(mesh::CreateBox(1, { 255, 0, 0, 255 }));
		obj.AddComponent(new Collision(box_, {}, { 100.0f, 100.0f }));

		Objectmanager_.AddObject(obj);
	}
	
}


//void JSON::UpdateLevel(StateManager* state_manager) //Engine
//{
//	if (saved_state_manager)
//		return;
//
//	saved_state_manager = state_manager;
//}
//
//void JSON::UpdateState(StateManager* state_manager) //State
//{
//	//if (saved_state_manager)
//		//return;
//
//	levels.SetObject();
//	LoadLevelDocument();
//	level_objects.SetObject();
//
//	saved_state_manager = state_manager;
//	currentstate = saved_state_manager->GetCurrentState();
//
//	for (std::map<std::string, std::unique_ptr<State>>::iterator
//		it = saved_state_manager->GetStateMap().begin();
//		it != saved_state_manager->GetStateMap().end(); it++)
//	{
//		if (currentstate == it->second.get())
//			currentstate_name = it->first;
//	}
//}
//
//void JSON::SaveAtEnd() //Engine
//{
//	//SaveAtEnd(saved_state_manager);
//	SaveAtEachDocument();
//}
//
//void JSON::SaveAtEachDocument() //State
//{
//	if (!levels.HasMember(currentstate_name.c_str()))
//		UpdateLevelToDocument(currentstate_name);
//
//	UpdateDocument(currentstate->GetObjectManager().get(), &level_objects);
//	SaveADocument("levels", &levels);
//	SaveADocument(currentstate_name, &level_objects);
//}
//
//void JSON::SaveAtEnd(StateManager* state_manager) //Engine
//{
//	std::string name;
//	State* currentstate;
//	Objectmanager* currentObjectM;
//
//	for (std::map<std::string, std::unique_ptr<State>>::iterator
//		it = state_manager->GetStateMap().begin(); it != state_manager->GetStateMap().end(); it++)
//	{
//		name = it->first;
//		currentstate = it->second.get();
//
//		currentObjectM = it->second.get()->GetObjectManager().get();
//		if (!currentObjectM) //if currentObejctmanager is empt, it means you didn't turn that level.
//			continue;
//
//		AddNewLevel(currentstate, name);
//		for (std::map<std::string, std::unique_ptr<rapidjson::Document>>::iterator
//			it2 = LevelDocuments.begin(); it2 != LevelDocuments.end(); it2++)
//		{
//			if(it2->first == name)
//			UpdateDocument(currentObjectM, it2->second.get());
//		}
//	}
//}
//
//void JSON::UpdateLevelToDocument(std::string statename)
//{
//	rapidjson::Value new_level_info(statename.c_str(), levels.GetAllocator());
//	rapidjson::Value new_level_name(rapidjson::kObjectType);
//	new_level_name.SetString(statename.c_str(),levels.GetAllocator());
//	levels.AddMember(new_level_name, new_level_info, levels.GetAllocator());
//
//}
//
//void JSON::AddNewLevel(State* current_state, std::string name)
//{
//	LevelDocuments.insert(std::make_pair(name,
//		new rapidjson::Document(rapidjson::kObjectType)));
//
//	//Level data
//	rapidjson::Value newLevel(rapidjson::kObjectType);
//	rapidjson::Value newLevelname(name.c_str(), levels.GetAllocator());
//	//add to level? member
//	newLevel.AddMember(Level, newLevelname, levels.GetAllocator());
//
//	std::string Levelcount = level_name; //temporary levelcountname
//	Levelcount.append(std::to_string(level_count));
//	//Add to document.
//	rapidjson::Value countofLevel(Levelcount.c_str(), levels.GetAllocator());
//	levels.AddMember(countofLevel, newLevel, levels.GetAllocator());
//	level_count++;
//}
//
//void JSON::UpdateDocument(Objectmanager* objectmanager, rapidjson::Document* document)
//{
//	for (auto& obj : Objectmanager_.GetObjectMap())
//	{
//		
//	}
//	for (std::map<std::string, std::unique_ptr<Object>>::iterator
//		it = objectmanager->GetObjectMap().begin(); it != objectmanager->GetObjectMap().end(); ++it)
//	{
//		if (!(document->HasMember(it->first.c_str())))
//			AddNewObject(it->second.get(), it->first, document);
//		//else
//		//	UpdateObject(it->second.get(), it->first, document);
//	}
//}
//
//void JSON::AddNewObject(Object* object, std::string name, rapidjson::Document* document)
//{
//	if (!object->GetMesh().IsVisible())
//		return;
//	rapidjson::Value newObjectData(rapidjson::kObjectType);
//	rapidjson::Document::AllocatorType& allocator = document->GetAllocator();
//
//	//Add Data of object///////////////////////////////////////
//	rapidjson::Value newObjectName(name.c_str(), allocator);
//
//	rapidjson::Value newObjectTranslation(rapidjson::kArrayType);
//	newObjectTranslation.PushBack(object->GetTransform().GetTranslation().x, allocator);
//	newObjectTranslation.PushBack(object->GetTransform().GetTranslation().y, allocator);
//
//	rapidjson::Value newObjectScale(rapidjson::kArrayType);
//	newObjectScale.PushBack(object->GetTransform().GetScale().x, allocator);
//	newObjectScale.PushBack(object->GetTransform().GetScale().y, allocator);
//
//	rapidjson::Value newObjectRotation(rapidjson::kObjectType);
//	newObjectRotation.SetFloat((object->GetTransform().GetRotation()));
//
//	rapidjson::Value newObjectDepth(rapidjson::kObjectType);
//	newObjectDepth.SetFloat(object->GetTransform().GetDepth());
//
//	rapidjson::Value newObjectGravity(rapidjson::kObjectType);
//	newObjectGravity.SetFloat(object->GetGravity());
//
//	rapidjson::Value newObjectTexture(object->texture_path.c_str(), allocator);
//
//	rapidjson::Value newObjectID(rapidjson::kObjectType);
//	newObjectID.SetInt(object->object_id);
//	 
//	////
//	rapidjson::Value newObjectSprite(rapidjson::kObjectType);
//	if (object->GetComponentByTemplate<Sprite>())
//		newObjectSprite.SetInt(1);
//	else
//		newObjectSprite.SetInt(0);
//
//	rapidjson::Value newObjectAnimation(rapidjson::kObjectType);
//	if (object->GetComponentByTemplate<Animation>())
//		newObjectAnimation.SetInt(1);
//	else
//		newObjectAnimation.SetInt(0);
//
//	rapidjson::Value newObjectCharacter(rapidjson::kObjectType);
//	if (object->GetComponentByTemplate<Character>())
//		newObjectCharacter.SetInt(1);
//	else
//		newObjectCharacter.SetInt(0);
//
//	rapidjson::Value newObjectCollision(rapidjson::kObjectType);
//	if (object->GetComponentByTemplate<Collision>())
//		newObjectCollision.SetInt(1);
//	else
//		newObjectCollision.SetInt(0);
//
//	newObjectData.AddMember(NAME, newObjectName, allocator);
//	newObjectData.AddMember(TRANSLATION, newObjectTranslation, allocator);
//	newObjectData.AddMember(ROTATION, newObjectRotation, allocator);
//	newObjectData.AddMember(SCALE, newObjectScale, allocator);
//	newObjectData.AddMember(DEPTH, newObjectDepth, allocator);
//	newObjectData.AddMember(GRAVITY, newObjectGravity, allocator);
//	newObjectData.AddMember(TEXTURE, newObjectTexture, allocator);
//	newObjectData.AddMember(ID, newObjectID, allocator);
//
//	newObjectData.AddMember(Sprite_, newObjectSprite, allocator);
//	newObjectData.AddMember(Animation_, newObjectAnimation, allocator);
//	newObjectData.AddMember(Character_, newObjectCharacter, allocator);
//	newObjectData.AddMember(Collision_, newObjectCollision, allocator);
//
//
//	rapidjson::Value nameofobject(name.c_str(), allocator);
//
//	//Add objectdata to document
//	document->AddMember(nameofobject, newObjectData, allocator);
//}
//
//
//void JSON::SaveDocument()
//{
//	//store objects
//	for (std::map<std::string, std::unique_ptr<rapidjson::Document>>
//		::iterator it = LevelDocuments.begin(); it != LevelDocuments.end(); ++it)
//	{
//		FILE* fp;
//		std::string filename = file_path;
//		filename.append(it->first);
//		filename.append(".json");
//		fopen_s(&fp, filename.c_str(), "wb");
//
//		char writeBuffer[65535];
//		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
//		rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
//		it->second.get()->Accept(writer);
//		fclose(fp);
//	}
//
//	//store levels
//	FILE* fp;
//	std::string filename = file_path;
//	filename.append("levels.json");
//	fopen_s(&fp, filename.c_str(), "wb");
//	char writeBuffer[65535];
//	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
//	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
//	levels.Accept(writer);
//	fclose(fp);
//}
//
//void JSON::LoadDocument()
//{
//	//load levels
//	LoadLevelDocument();
//
//	for (rapidjson::Value::ConstMemberIterator itr = levels.MemberBegin();
//		itr != levels.MemberEnd(); ++itr)
//	{
//		//Add new document
//		rapidjson::Document *newLevelObjectData = new rapidjson::Document(rapidjson::kObjectType);
//
//		std::string file_name = file_path;
//		file_name.append(itr->name.GetString());
//		file_name.append(".json");
//		FILE* fp;
//		fopen_s(&fp, file_name.c_str(), "rb");
//		char readBuffer[65536];
//		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
//		newLevelObjectData->ParseStream(is);
//		fclose(fp);
//
//		LevelDocuments.insert(std::make_pair(itr->name.GetString(), newLevelObjectData));
//	}
//}
//
//void JSON::LoadLevelDocument()
//{
//	FILE* fp;
//	fopen_s(&fp, "asset/JsonFiles/levels.json", "rb");
//	char readBuffer[65536];
//	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
//	levels.ParseStream(is);
//	fclose(fp);
//}
//
//rapidjson::Document* JSON::GetDocumentofLevel(std::string level_name)
//{
//	for (std::map<std::string, std::unique_ptr<rapidjson::Document>>
//		::iterator it = LevelDocuments.begin(); it != LevelDocuments.end(); ++it)
//	{
//		if (it->first == level_name)
//			return it->second.get();
//	}
//
//	return nullptr;
//}
//
//void JSON::GetLoadLevel(std::string state_name, std::map<std::string, Object>* state_object)
//{
//	rapidjson::Document load_document;
//	FILE* fp;
//	std::string file_name = file_path;
//	file_name.append(state_name);
//	file_name.append(".json");
//	fopen_s(&fp, file_name.c_str(), "rb");
//	char readBuffer[65535];
//	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
//	load_document.ParseStream(is);
//	fclose(fp);
//
//	for (rapidjson::Value::ConstMemberIterator itr = load_document.MemberBegin();
//		itr != load_document.MemberEnd(); itr++)
//	{
//		std::string load_object_name = itr->name.GetString();
//		vector2 load_scale = { itr->value["scale"][0].GetFloat(), itr->value["scale"][1].GetFloat() };
//		vector2 load_translation = { itr->value["translation"][0].GetFloat(), itr->value["translation"][1].GetFloat() };
//		float load_rotation = itr->value["rotation"].GetFloat();
//		float load_depth = itr->value["depth"].GetFloat();
//
//		//int sprite_ = itr->value["sprite"].GetInt();
//
//		Object new_object;
//		new_object.SetScale(load_scale);
//		new_object.SetTranslation(load_translation);
//		new_object.SetRotation(load_rotation);
//		new_object.SetDepth(load_depth);
//		new_object.texture_path = itr->value["texture"].GetString();
//		new_object.object_id = itr->value["id"].GetInt();
//
//		if (itr->value["sprite"].GetInt())
//			new_object.component_type_id = 0;
//		else if (itr->value["animation"].GetInt())
//			new_object.component_type_id = 1;
//		else if (itr->value["character"].GetInt())
//			new_object.component_type_id = 2;
//		else if (itr->value["collision"].GetInt())
//			new_object.component_type_id = 3;
//
//		state_object->insert(std::pair<std::string, Object>(load_object_name, new_object));
//	}
//}
//
//void JSON::SaveADocument(std::string docu_name, rapidjson::Document* docu)
//{
//	FILE* fp;
//	std::string filename = file_path + docu_name + ".json";
//	fopen_s(&fp, filename.c_str(), "wb");
//
//	char writeBuffer[65535];
//	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
//	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
//	docu->Accept(writer);
//	fclose(fp);
//}
//
//void JSON::SaveOtherLevel
//(std::string state_name, std::map<std::string, std::unique_ptr<Object>>*state_object)
//{
//	if (!levels.HasMember(state_name.c_str()))
//		UpdateLevelToDocument(state_name);
//
//	rapidjson::Document* new_document = new rapidjson::Document;
//	new_document->SetObject();
//	for (auto itr = state_object->begin(); itr != state_object->end(); itr++)
//		AddNewObject(itr->second.get(), itr->first, new_document);
//
//	SaveADocument(state_name, new_document);
//	delete new_document;
//}