#pragma once
#include <iostream>
#include "Component.hpp"
#include "Input.hpp"
#include "Object.hpp"
#include "StateManager.hpp"
#include "Transform.hpp"
#include "vector2.hpp"
#include "Tile_Map.hpp"
#include "RigidBody.hpp"
#include "Timer.hpp"

enum class Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SIZE
};
enum class MovementType
{
	NONE,
	ONEWAY,
	ROUND,
	SIZE
};

class MovingObject : public Component
{
public:
	     MovingObject(float Distance, vector2 InitPosition, float Velocity, Direction WhichWay, MovementType Type, float MoveTime);
	bool Initialize(Object* Ob) override;
	void Update(float dt) override;
	void Delete() override;
	void MoveOneWay(Direction WhichWay, float dt);
	void MoveRound(Direction WhichWay);
public:
	vector2   GetInitPosition() const { return m_InitPosition; }
	vector2   GetGoalPosition() const { return m_GoalPosition; }
	float     GetDistance() const     { return m_Distance;     }
	Direction GetDirection() const    { return m_WhichWay;     }
	MovementType GetMoveType() const  { return m_MoveType;     }
	float     GetVelocity() const     { return m_Velocity;     }
	float     GetDt() const { return m_dt; }
	float     GetMoveTime() const { return m_MoveTime; }
	void SetInitPosition(vector2 InitPosition) { m_InitPosition = InitPosition; }
	void SetGoalPosition(vector2 GoalPosition) { m_GoalPosition = GoalPosition; }
	void SetDistance(float Distance)           { m_Distance = Distance;         }
	void SetDirection(Direction WhichWay)      { m_WhichWay = WhichWay;         }
	void SetVelocity(float Velocity)		   { m_Velocity = Velocity;         }
	void SetDt(float dt) { m_dt = dt; }
	void SetMoveTime(float time) { m_MoveTime = time; }
	void SetMovementType(MovementType type) { m_MoveType = type; }
public:
	void SetRoundBoundary(Direction WhichWay);
private:
	float        m_dt = 0.0f;
	vector2      m_InitPosition{};
	vector2      m_GoalPosition{};
	float        m_Distance = 0.0f;
	float        m_Velocity = 0.0f;
	float	     m_MoveTime = 0.0f;
	Direction    m_WhichWay = Direction::NONE;
	MovementType m_MoveType = MovementType::NONE;
};