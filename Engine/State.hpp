/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: State.hpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/

#pragma once
#include "Objectmanager.hpp"
#include <vector2.hpp>
#include "AudioManager.hpp"
#include "StateManager.hpp"
#include "JSON.hpp"

class JSON;

class State
{
public:
	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void ShutDown() = 0;

	void SetCamera() { iscamera = true; }
	bool IsCamera() { return iscamera; }

	virtual bool IsLevelChange() { return level_change; }
	virtual bool IsBackToMenu() { return back_to_menu; }
	virtual std::string GetNextLevel() { return change_level; }
	virtual void ChangeLevel(std::string ID);
	virtual void BackToMenu();

	void ResetLevelChange() { level_change = false; }
	void ResetBackToMenu() { back_to_menu = false; }
	void SaveLevel();
	void LoadLevel();
	void LoadLevel(const std::string& current_level);
	void UnLoad();

	void SetPlayerObjectPointer(Object* obj) { player_obj = obj; }
	void SetCaptureObjectPointer(Object* obj) { capture_obj = obj; }
	void SetLevelChange(bool change) { level_change = change; }

	void SetPlayerPosition(vector2 pos) { player_pos = pos; }
	vector2 GetPlayerPosition() { return player_pos; }
	void SetStartPosition(vector2 pos) { start_pos = pos; }
	vector2 GetStartPosition() { return start_pos; }
	void SetLevelIndicator(const std::string& id) { level_indicator = id; }
	std::string GetLevelIndicator() { return level_indicator; }
	State_Information GetCurrentStateInfo() { return information_; }

	Object* GetPlayerObjectPointer() { return player_obj; }
	Object* GetCaptureObjectPointer() { return capture_obj; }

	State_Information information_ = State_Information::None;
	vector2 camera_center{};


        void CreateCaptureCamera();
        void CreatePlayer();

public:
	std::string level_indicator;
	std::string change_level;
private:
	Object* player_obj = nullptr;
	Object* capture_obj = nullptr;

	vector2 player_pos;
	vector2 start_pos;

	bool iscamera = false;
	bool level_change = false;
	bool back_to_menu = false;
};
