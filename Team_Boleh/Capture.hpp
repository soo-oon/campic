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

	bool IsCheese() { return cheese; }
	void SetCheese(bool condition) { cheese = condition; }
	void SetZoomMinMax(float max, float min = 1.0f);

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
			obj->SetDepth(0.9f);
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

	bool IsCaptureArea();
	void Capturing();
	void CreateCaptureObject();
	void CreatePolaroidObject();
	void CameraZoom();
	void CameraZoomInOut();
	void SetOrigianlSize();
    void ZoomObjectUpdate(float dt);
	void CollisionChangeZoomInOut(Object* obj, Collision* collision);

	void SlowMode();

    Filter m_c_filter = Filter::None;

	bool iscreate = false;
	bool cheese = false;
	bool is_runtime_change = false;
	bool isoutside = false;

	float temp_zoom = 1.0f;
	float zoom = 1.0f;
	vector2 reset_pos;
	float zoom_max_value = 0.0f;
	float zoom_min_value = 0.0f;

	Object* zoombutton = nullptr;
	Object* zoomobject = nullptr;
	Object* player = nullptr;
	std::vector<std::pair<vector2, Object*>> original_scale;
	std::vector<Object*> capture_area_contian_object;
	std::vector<Object*> not_area_contian_object;
	std::vector<Object*> temporary_obj_storage;
	std::vector<Polaroid*> polaroid_object;
};