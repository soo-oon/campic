#include "JSON.hpp"
#include "Status.hpp"
#include "Animation.hpp"
#include <iostream>
#include "Particle.hpp"

JSON JSON_;

bool JSON::Initialize()
{
	ObjectDocument.SetObject();

	return true;
}

void JSON::Update(float /*dt*/)
{
}

void JSON::Quit()
{
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
	Value objRigidBodyTree;
	Value objCollisionTree(kArrayType);
	Value objParticleTree(kArrayType);
	
	objTree.SetObject();
	objTransformTree.SetObject();
	objAnimationTree.SetObject();
	objCameraTree.SetObject();
	objStatusTree.SetObject();
	objSpriteTree.SetObject();
	objRigidBodyTree.SetObject();
	objCollisionTree.SetObject();
	objParticleTree.SetObject();

	objTransformTree = ComponentTransform(obj);

	if (obj->GetComponentByTemplate<Status>() != nullptr)
	{
		objStatusTree = ComponentStatus(obj);
		if (objStatusTree.FindMember("Type")->value.FindMember("Enum")->value == "Camera")
		{
			objCameraTree = ComponentCamera(obj);
			objTree.AddMember("Camera", objCameraTree, ObjectDocument.GetAllocator());
		}
	}
	if(obj->GetComponentByTemplate<Animation>() != nullptr)
		objAnimationTree = ComponentAnimation(obj);

	//if(obj->GetComponentByTemplate<Camera>() != nullptr)
		//objCameraTree = ComponentCamera(obj);
	
	if(obj->GetComponentByTemplate<Sprite>() != nullptr)
		objSpriteTree = ComponentSprite(obj);
	
	if (obj->GetComponentByTemplate<RigidBody>() != nullptr)
		objRigidBodyTree.SetBool(true);
	else
		objRigidBodyTree.SetBool(false);

	if(obj->GetComponentByTemplate<Collision>() != nullptr)
		objCollisionTree = ComponentCollision(obj);
	
	if(obj->GetComponentByTemplate<Particle>() != nullptr)
		objParticleTree = ComponentParticle(obj);

	objTree.AddMember("Status", objStatusTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Transform", objTransformTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Sprite", objSpriteTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Animation", objAnimationTree, ObjectDocument.GetAllocator());
	objTree.AddMember("RigidBody", objRigidBodyTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Collision", objCollisionTree, ObjectDocument.GetAllocator());
	
	ObjectDocument.AddMember("Object", objTree, ObjectDocument.GetAllocator());

	ObjectDocument.Parse(ObjectBuffer.GetString());

	SaveObjectsToJson();
}

Value JSON::ComponentAnimation(Object* obj)
{
	Value objAnimationTree(kArrayType);
	Value objAnimationMap(kArrayType);
	Value objAnimation;
	Value current_animation, previous_animation;
	std::vector<Value*> animation_string;
	std::vector<Value*> animation_map;

	//Animation_Information class
	objAnimationTree.SetObject();
	objAnimationMap.SetObject();
	current_animation.SetObject();
	previous_animation.SetObject();

	auto animation_info = obj->GetComponentByTemplate<Animation>();

	for (auto& temp : animation_info->GetAnimationMap())
	{
		int i = 0;
		Value animation_path, id, path;
		Value animation_info_;
		Value animation_is_repeats;
		Value animation_pc_coordinate;

		animation_path.SetObject();
		animation_info_.SetObject();
		animation_is_repeats.SetObject();
		animation_pc_coordinate.SetObject();

		id.SetString(temp.first.c_str(), ObjectDocument.GetAllocator());
		path.SetString(temp.second.path.c_str(), ObjectDocument.GetAllocator());

		animation_path.AddMember("id", id, ObjectDocument.GetAllocator());
		animation_path.AddMember("path", path, ObjectDocument.GetAllocator());
		animation_is_repeats.SetBool(temp.second.is_repeats);
		animation_info_.AddMember("image_frames", temp.second.image_frames, ObjectDocument.GetAllocator());
		animation_info_.AddMember("update_frames", temp.second.update_frames, ObjectDocument.GetAllocator());
		animation_info_.AddMember("is_repeats", animation_is_repeats, ObjectDocument.GetAllocator());

		animation_string.push_back(&animation_path);
		animation_map.push_back(&animation_info_);

		objAnimationMap.AddMember("path", *animation_string.at(i), ObjectDocument.GetAllocator());
		objAnimationMap.AddMember("info", *animation_map.at(i), ObjectDocument.GetAllocator());
		++i;
	}

	objAnimationTree.AddMember("map", objAnimationMap, ObjectDocument.GetAllocator());

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
		case ObjectType::Camera:
		{
			objTypeVal.SetInt(8);
			objTypeString.SetString("Camera");
			break;
		}
		case ObjectType::None:
		{
			objTypeVal.SetInt(9);
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
	Value path, flip;

	objSpriteTree.SetObject();
	path.SetObject();

	auto obj_info = obj->GetComponentByTemplate<Sprite>();

	path.SetString(obj_info->GetPath().c_str(), ObjectDocument.GetAllocator());
	flip.SetBool(obj_info->IsFlip());

	objSpriteTree.AddMember("is_flip", flip, ObjectDocument.GetAllocator());
	objSpriteTree.AddMember("image_path", path, ObjectDocument.GetAllocator());

	return objSpriteTree;
}

Value JSON::ComponentCollision(Object * obj)
{
	Value collision_type;
	collision_type.SetObject();

	auto type = obj->GetComponentByTemplate<Collision>()->GetCollisionType();

	switch(type)
	{
		case CollisionType::box_ :
		{
			collision_type.AddMember("id", static_cast<int>(type), ObjectDocument.GetAllocator());
			collision_type.AddMember("enum", "box", ObjectDocument.GetAllocator());
			break;
		}
		case CollisionType::circle_:
		{
			collision_type.AddMember("id", static_cast<int>(type), ObjectDocument.GetAllocator());
			collision_type.AddMember("enum", "circle", ObjectDocument.GetAllocator());
			break;
		}
		case CollisionType::triangle_:
		{
			collision_type.AddMember("id", static_cast<int>(type), ObjectDocument.GetAllocator());
			collision_type.AddMember("enum", "triangle", ObjectDocument.GetAllocator());
			break;
		}
		default:
			break;
	}

	return collision_type;
}

Value JSON::ComponentParticle(Object * obj)
{
	return Value();
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

	for (auto& temp : ObjectDocument.GetObject())
	{
		Value& obj_array = temp.value;

		Value status, transform, animation, sprite, rigid_body, collision, particle;
		Object obj;

		status.SetObject();
		transform.SetObject();
		sprite.SetObject();
		animation.SetObject();
		rigid_body.SetObject();
		collision.SetObject();
		particle.SetObject();

		status = obj_array.FindMember("Status")->value;
		transform = obj_array.FindMember("Transform")->value;
		sprite = obj_array.FindMember("Sprite")->value;
		animation = obj_array.FindMember("Animation")->value;
		rigid_body = obj_array.FindMember("RigidBody")->value;
		collision = obj_array.FindMember("Collision")->value;
		//animation = obj_array.FindMember("Animation")->value;


		// Status
		int obj_type = status.FindMember("Type")->value.FindMember("Value")->value.GetInt();
		int hp_ = status.FindMember("HP")->value.GetInt();
		int attack_damage = status.FindMember("Damage")->value.GetInt();
		float speed = status.FindMember("Speed")->value.GetFloat();
		bool is_alive = status.FindMember("isAlive")->value.GetBool();

		obj.AddComponent(new Status(static_cast<ObjectType>(obj_type), hp_, attack_damage, speed, is_alive));

		// Transform
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

		// Sprite
		bool is_flip = false;
		std::string path;

		if (sprite.HasMember("image_path"))
		{
			path = sprite.FindMember("image_path")->value.GetString();
			is_flip = sprite.FindMember("is_flip")->value.GetBool();

			obj.AddComponent(new Sprite(path));
			obj.GetComponentByTemplate<Sprite>()->SetFlip(is_flip);
		}

		// Animation
		std::vector<std::string> id, ani_path;
		std::vector<int> image_frame;
		std::vector<float> update_frame;
		std::vector<bool> is_repeat;

		if(animation.HasMember("map"))
		{
			for (auto& temp_ : animation.FindMember("map")->value.GetObject())
			{
				Value& map_array = animation.FindMember("map")->value;
			
				id.push_back(map_array.FindMember("path")->value.FindMember("id")->value.GetString());
				ani_path.push_back(map_array.FindMember("path")->value.FindMember("path")->value.GetString());
				image_frame.push_back(map_array.FindMember("info")->value.FindMember("image_frames")->value.GetInt());
				update_frame.push_back(map_array.FindMember("info")->value.FindMember("update_frames")->value.GetFloat());
				is_repeat.push_back(map_array.FindMember("info")->value.FindMember("is_repeats")->value.GetBool());
			}

			obj.AddComponent(new Animation(ani_path.at(0), id.at(0),image_frame.at(0), update_frame.at(0), is_repeat.at(0)));

			for(int i = 1; i < id.size(); i++)
			{
				obj.GetComponentByTemplate<Animation>()->AddAnimaition(ani_path.at(i), id.at(i), image_frame.at(i), 
					update_frame.at(i), is_repeat.at(i));
			}
		}

		// RigidBody
		bool is_rigid = false;
		is_rigid = rigid_body.GetBool();
		
		if (is_rigid)
			obj.AddComponent(new RigidBody());

		// Collision
		CollisionType type;
		type = static_cast<CollisionType>(collision.FindMember("id")->value.GetInt());
		
		obj.AddComponent(new Collision(type));

		// Particle


		obj.SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));
		obj.AddComponent(new Collision(box_, {}, { 100.0f, 100.0f }));

		Objectmanager_.AddObject(obj);
	}
}
