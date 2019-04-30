#pragma once

// From -1 to +1
// -1.f will be in front

const float CAPTURE_OBJECT = -0.9f;
const float POLAROID = 0.9f;
const float GAME_OBJECT = -0.5f;
const float HUD_OBJECT = -0.2f;
const float HUD_BUTTON = -0.65f;
const float BACKGROUND = -0.1f;

enum class ObjectDepth
{
	CAPTURE_OBJECT,
	POLAROID,
	GAME_OBJECT,
	HUD_OBJECT,
	HUD_BUTTON,
	BACKGROUND
};