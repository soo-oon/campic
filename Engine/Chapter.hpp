#pragma once

#include "Component.hpp"

class Chapter : public Component
{
public:
	Chapter() = default;
	Chapter(int chapter_, int level_) :  chapter(chapter_), level(level_) {}

	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;

	int GetChapter() { return chapter; }
	int GetLevel() { return level; }

private:
	int chapter = 0;
	int level = 0;
};

