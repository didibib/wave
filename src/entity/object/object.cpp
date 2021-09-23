#include "pch/wavepch.h"
#include "object.h"

namespace Wave
{
	Object::Object() :
		m_Position(0.f, 0.f, 0.f), m_Forward(0.f, 0.f, -1.f), m_Up(0.f, 1.f, 0.f), m_Right(1.f, 0.f, 0.f), m_WorldUp(0.f, 1.f, 0.f), m_Model(1.f)
	{
	}

	Object::Object(glm::vec3 pos) : 
		m_Forward(0.f, 0.f, -1.f), m_Up(0.f, 1.f, 0.f), m_Right(1.f, 0.f, 0.f), m_WorldUp(0.f, 1.f, 0.f), m_Model(1.f)
	{
		SetPos(pos);
	}

	void Object::SetPos(glm::vec3 pos)
	{
		m_Position = pos;
	}

	void Object::SetPos(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}
}


