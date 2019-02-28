#include "JSON.hpp"
#include "Status.hpp"
#include "Animation.hpp"
#include <iostream>
#include "Particle.hpp"
#include "Particle_Generator.hpp"
#include "Font.hpp"

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
	Value objSoundTree(kArrayType);
	Value objFontTree(kArrayType);
	
	objTree.SetObject();
	objTransformTree.SetObject();
	objAnimationTree.SetObject();
	objCameraTree.SetObject();
	objStatusTree.SetObject();
	objSpriteTree.SetObject();
	objRigidBodyTree.SetObject();
	objCollisionTree.SetObject();
	objParticleTree.SetObject();
	objSoundTree.SetObject();
	objFontTree.SetObject();

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
	
	if(obj->GetComponentByTemplate<Particle_Generator>() != nullptr)
		objParticleTree = ComponentParticle(obj);

	if (obj->GetComponentByTemplate<Sound>() != nullptr)
		objSoundTree = ComponentSound(obj);

	if (obj->GetComponentByTemplate<Font>() != nullptr)
		objFontTree = ComponentFont(obj);

	objTree.AddMember("Status", objStatusTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Transform", objTransformTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Sprite", objSpriteTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Animation", objAnimationTree, ObjectDocument.GetAllocator());
	objTree.AddMember("RigidBody", objRigidBodyTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Collision", objCollisionTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Particle", objParticleTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Sound", objSoundTree, ObjectDocument.GetAllocator());
	objTree.AddMember("Font", objFontTree, ObjectDocument.GetAllocator());
	
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

	objType.AddMember("id", objTypeVal, ObjectDocument.GetAllocator());
	objType.AddMember("enum", objTypeString, ObjectDocument.GetAllocator());

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
	Value particleTree(kArrayType);
	Value start_velocity, random_velocity, particle_size,emit_size, path, isActive;
	
	particleTree.SetObject();
	start_velocity.SetObject();
	random_velocity.SetObject();
	particle_size.SetObject();
	emit_size.SetObject();
	isActive.SetObject();
	path.SetObject();

	auto particle_info = obj->GetComponentByTemplate<Particle_Generator>();

	particleTree.AddMember("emit_rate", particle_info->GetEmitRate(), ObjectDocument.GetAllocator());
	particleTree.AddMember("life_time", particle_info->GetLifeTimeControl(), ObjectDocument.GetAllocator());
	particleTree.AddMember("size_variance", particle_info->GetSizeVarianceControl(), ObjectDocument.GetAllocator());
	particleTree.AddMember("color_duration", particle_info->GetColorDuration(), ObjectDocument.GetAllocator());

	start_velocity.AddMember("x", particle_info->GetStartVelocity().x, ObjectDocument.GetAllocator());
	start_velocity.AddMember("y", particle_info->GetStartVelocity().y, ObjectDocument.GetAllocator());
	random_velocity.AddMember("x", particle_info->GetRandomVelocity().x, ObjectDocument.GetAllocator());
	random_velocity.AddMember("y", particle_info->GetRandomVelocity().y, ObjectDocument.GetAllocator());
	particle_size.AddMember("x", particle_info->GetParticleSize().x, ObjectDocument.GetAllocator());
	particle_size.AddMember("y", particle_info->GetParticleSize().y, ObjectDocument.GetAllocator());
	emit_size.AddMember("x", particle_info->GetEmitSize().x, ObjectDocument.GetAllocator());
	emit_size.AddMember("y", particle_info->GetEmitSize().y, ObjectDocument.GetAllocator());
	isActive.SetBool(particle_info->GetIsActive());
	path.SetString(particle_info->GetPath().c_str(), ObjectDocument.GetAllocator());

	particleTree.AddMember("start_velocity", start_velocity, ObjectDocument.GetAllocator());
	particleTree.AddMember("random_velocity", random_velocity, ObjectDocument.GetAllocator());
	particleTree.AddMember("particle_size", particle_size, ObjectDocument.GetAllocator());
	particleTree.AddMember("emit_size", emit_size, ObjectDocument.GetAllocator());
	particleTree.AddMember("isActive", isActive, ObjectDocument.GetAllocator());
	particleTree.AddMember("path", path, ObjectDocument.GetAllocator());

	return particleTree;
}

Value JSON::ComponentSound(Object * obj)
{
	Value container(kArrayType);
	Value paths;

	container.SetObject();
	paths.SetObject();

	auto sound_info = obj->GetComponentByTemplate<Sound>();
	auto path_container = sound_info->GetSoundPaths();

	for(auto& temp : path_container)
	{
		paths.SetString(temp.c_str(), ObjectDocument.GetAllocator());
		container.AddMember("path", paths, ObjectDocument.GetAllocator());
	}

	return container;
}

Value JSON::ComponentFont(Object * obj)
{
	Value container(kArrayType);
	Value paths, text;

	container.SetObject();
	paths.SetObject();
	text.SetObject();

	auto font_info = obj->GetComponentByTemplate<Font>();

	text.SetString(font_info->GetText().c_str(), ObjectDocument.GetAllocator());
	paths.SetString(font_info->GetPath().c_str(), ObjectDocument.GetAllocator());

	container.AddMember("text", text, ObjectDocument.GetAllocator());
	container.AddMember("path", paths, ObjectDocument.GetAllocator());

	return container;
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
		Object* obj = new Object();

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
		particle = obj_array.FindMember("Particle")->value;

		// Status
		int obj_type = status.FindMember("Type")->value.FindMember("id")->value.GetInt();
		int hp_ = status.FindMember("HP")->value.GetInt();
		int attack_damage = status.FindMember("Damage")->value.GetInt();
		float speed = status.FindMember("Speed")->value.GetFloat();
		bool is_alive = status.FindMember("isAlive")->value.GetBool();

		obj->AddComponent(new Status(static_cast<ObjectType>(obj_type), hp_, attack_damage, speed, is_alive));

		// Transform
		vector2 pos, scale;
		float rotation;

		pos.x = transform.FindMember("position")->value.FindMember("x")->value.GetFloat();
		pos.y = transform.FindMember("position")->value.FindMember("y")->value.GetFloat();
		scale.x = transform.FindMember("scale")->value.FindMember("x")->value.GetFloat();
		scale.y = transform.FindMember("scale")->value.FindMember("y")->value.GetFloat();
		rotation = transform.FindMember("rotation")->value.GetFloat();

		obj->SetTranslation(pos);
		obj->SetScale(scale);
		obj->SetRotation(rotation);

		obj->SetMesh(mesh::CreateBox(1, { 255, 255, 255, 255 }));

		// Sprite
		bool is_flip = false;
		std::string path;

		if (sprite.HasMember("image_path"))
		{
			path = sprite.FindMember("image_path")->value.GetString();
			is_flip = sprite.FindMember("is_flip")->value.GetBool();

			obj->AddComponent(new Sprite(path));
			obj->GetComponentByTemplate<Sprite>()->SetFlip(is_flip);
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

			obj->AddComponent(new Animation(ani_path.at(0), id.at(0),image_frame.at(0), update_frame.at(0), is_repeat.at(0)));

			for(int i = 1; i < id.size(); i++)
			{
				obj->GetComponentByTemplate<Animation>()->AddAnimaition(ani_path.at(i), id.at(i), image_frame.at(i),
					update_frame.at(i), is_repeat.at(i));
			}
		}

		// RigidBody
		bool is_rigid = false;
		is_rigid = rigid_body.GetBool();
		
		if (is_rigid)
			obj->AddComponent(new RigidBody());

		// Collision
		CollisionType type;
		type = static_cast<CollisionType>(collision.FindMember("id")->value.GetInt());
		
		obj->AddComponent(new Collision(type));

		// Particle
		vector2 start, random, particle_size, emit_size;
		

		if (particle.HasMember("emit_rate"))
		{
			int emit_rate = particle.FindMember("emit_rate")->value.GetInt();
			auto life_time = particle.FindMember("life_time")->value.GetFloat();
			auto size_variance = particle.FindMember("size_variance")->value.GetFloat();
			auto color_duration = particle.FindMember("color_duration")->value.GetFloat();

			start.x = particle.FindMember("start_velocity")->value.FindMember("x")->value.GetFloat();
			start.y = particle.FindMember("start_velocity")->value.FindMember("y")->value.GetFloat();
			random.x = particle.FindMember("random_velocity")->value.FindMember("x")->value.GetFloat();
			random.y = particle.FindMember("random_velocity")->value.FindMember("y")->value.GetFloat();
			particle_size.x = particle.FindMember("particle_size")->value.FindMember("x")->value.GetFloat();
			particle_size.y = particle.FindMember("particle_size")->value.FindMember("y")->value.GetFloat();
			emit_size.x = particle.FindMember("emit_size")->value.FindMember("x")->value.GetFloat();
			emit_size.y = particle.FindMember("emit_size")->value.FindMember("y")->value.GetFloat();
			bool isActive = particle.FindMember("isActive")->value.GetBool();

			std::string particle_path = particle.FindMember("path")->value.GetString();
				
			obj->AddComponent(new Particle_Generator(emit_rate, life_time, size_variance,
					color_duration, start, random, particle_size, emit_size, particle_path, isActive));
		}
		Objectmanager_.AddObject(obj);
	}
}
