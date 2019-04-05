#pragma once
#include "Component.hpp"
#include <vector>
#include "vector2.hpp"
#include "RandomFunction.hpp"
#include "Object.hpp"
#include "Collision.hpp"

class Capture : public Component
{
public:
	Capture(vector2 pos) : reset_pos(pos){}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	void SetResetPosition(vector2 size) { reset_pos = size; }
	vector2 GetResetPosition()const { return reset_pos; }
	void SetFilter(Filter filter) { m_c_filter = filter; }

	Filter GetFilter() { return m_c_filter; }
	void SlowMode(float fric);

	bool IsCheese() { return cheese; }
	void SetCheese(bool condition) { cheese = condition; }

private:
	class Polaroid
	{
	public:
		Polaroid(Object* obj_)
		{
			float angle = RandomNumberGenerator(-45.0f, 45.0f);

			obj = new Object();
			obj->SetTranslation(obj_->GetTransform().GetTranslation());
			obj->SetScale({ 150, 170 });
			obj->SetRotation(angle);
			obj->SetObjectType(ObjectType::Polaroid);
			obj->SetMesh(mesh::CreateBox(1, {255,255,255,75}));
			obj->AddComponent(new Sprite("asset/images/polaroid.png"));
		}

		void Update();
		bool IsDead() { return isdead; }
		Object* GetObject() { return obj; }

	private:
		Object* obj = nullptr;
		bool isdead = false;
	};
	void Capturing();
	void CreateCaptureObject();
	void CreatePolaroidObject();
    Filter m_c_filter = Filter::None;

	bool iscreate = false;
	bool cheese = false;
	float zoom = 1.0f;
	vector2 reset_pos;
	std::vector<Object*> capture_object;
	std::vector<Polaroid*> polaroid_object;
};
