#pragma once
#include <string>
#include "LevelJson.hpp"
#include "Component.hpp"

class UI : public Component
{
public:
	UI(std::string id_);

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

public:
	void SetIsLock(bool islock) { IsLock = islock; }
	void SetId(const std::string& id_) { id = id_; }

	void TriggerLevelLock(std::string level_id, bool isclear = true);

	bool GetIsLock() { return IsLock; }
	std::string GetId() const { return id; }

private:
	std::string id;
	bool IsLock = false;
};

