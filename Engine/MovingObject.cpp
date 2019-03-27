#include "MovingObject.hpp"

bool MovingObject::Initialize(Object* Ob)
{
	if (object == nullptr)
	{
		object = Ob;
	}
	return true;
}
void MovingObject::Update(float dt)
{
	if (m_MoveType == MovementType::ONEWAY)
	{
		MoveOneWay(m_WhichWay, dt);
	}
	if (m_MoveType == MovementType::ROUND)
	{
		MoveRound(m_WhichWay);
	}
}
void MovingObject::Delete()
{
	//EMPTY FUNCTION
}
MovingObject::MovingObject(float Distance, vector2 InitPosition, float Velocity, Direction WhichWay, MovementType MoveType, float MoveTime)
{
	m_InitPosition = InitPosition;
	m_GoalPosition = m_InitPosition;
	m_Distance     = Distance * TILE_SIZE;
	m_WhichWay	   = WhichWay;
	m_Velocity     = Velocity;
	m_MoveType     = MoveType;
	m_MoveTime	   = MoveTime;
	SetRoundBoundary(m_WhichWay);
}
void MovingObject::MoveOneWay(Direction WhichWay, float dt)
{
	m_dt += dt;
	if (m_dt >= m_MoveTime)
	{
		if (m_WhichWay == Direction::UP)
		{
			object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0.0f, m_Velocity });
			if (object->GetTransform().GetTranslation().y >= m_InitPosition.y + m_Distance)
			{
				object->SetIsDead(true);
			}
		}
		else if (m_WhichWay == Direction::DOWN)
		{
			object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0.0f, -m_Velocity });
			if (object->GetTransform().GetTranslation().y <= m_InitPosition.y - m_Distance)
			{
				object->SetIsDead(true);
			}
		}
		else if (m_WhichWay == Direction::LEFT)
		{
			object->GetComponentByTemplate<RigidBody>()->SetVelocity({ -m_Velocity, 0.0f });
			if (object->GetTransform().GetTranslation().x <= m_InitPosition.x - m_Distance)
			{
				object->SetIsDead(true);
			}
		}
		else if (m_WhichWay == Direction::RIGHT)
		{
			object->GetComponentByTemplate<RigidBody>()->SetVelocity({ m_Velocity, 0.0f });
			if (object->GetTransform().GetTranslation().x >= m_InitPosition.x + m_Distance)
			{
				object->SetIsDead(true);
			}
		}
		else
		{
			m_dt = 0.0f;
			return;
		}
		m_dt = 0.0f;
	}
}
void MovingObject::MoveRound(Direction WhichWay)
{
	switch (WhichWay)
	{
	case Direction::UP:
		 if(object->GetTransform().GetTranslation().y <= m_GoalPosition.y)
		 {
			object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0.0f, m_Velocity });
		 }
		 else
		 {
			 SetRoundBoundary(Direction::DOWN);
		 }
		break;
	case Direction::DOWN:
		if(object->GetTransform().GetTranslation().y >= m_GoalPosition.y)
		{
			object->GetComponentByTemplate<RigidBody>()->SetVelocity({ 0.0f, -m_Velocity });
		}
		else
		{
			SetRoundBoundary(Direction::UP);
		}
		break;
	case Direction::LEFT:
		if (object->GetTransform().GetTranslation().x >= m_GoalPosition.x)
		{
			object->GetComponentByTemplate<RigidBody>()->SetVelocity({ -m_Velocity, 0.0f });
		}
		else
		{
			SetRoundBoundary(Direction::RIGHT);
		}
		break;
	case Direction::RIGHT:
		if (object->GetTransform().GetTranslation().x <= m_GoalPosition.x)
		{
			object->GetComponentByTemplate<RigidBody>()->SetVelocity({ m_Velocity, 0.0f });
		}
		else
		{
			SetRoundBoundary(Direction::LEFT);
		}
		break;
	default:
		break;
	}
}
void MovingObject::SetRoundBoundary(Direction WhichWay)
{
	if (WhichWay == Direction::UP)
	{
		m_GoalPosition.y += m_Distance;
		m_WhichWay = Direction::UP;
	}
	else if (WhichWay == Direction::DOWN)
	{
		m_GoalPosition.y -= m_Distance;
		m_WhichWay = Direction::DOWN;
	}
	else if (WhichWay == Direction::LEFT)
	{
		m_GoalPosition.x -= m_Distance;
		m_WhichWay = Direction::LEFT;
	}
	else if (WhichWay == Direction::RIGHT)
	{
		m_GoalPosition.x += m_Distance;
		m_WhichWay = Direction::RIGHT;
	}
	else
	{
		return;
	}
}