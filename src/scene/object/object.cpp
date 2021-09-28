#include "pch/wavepch.h"
#include "object.h"

namespace Wave
{
	Object::Object() :
		m_Position(0.f, 0.f, 0.f), m_WorldUp(0.f, 1.f, 0.f), m_Model(1.f)
	{
	}

	void Object::Translate(glm::vec3 translation)
	{
		m_Model = glm::translate(m_Model, translation);
	}

	void Object::Rotate(float angleInRadians, glm::vec3 axis)
	{
		m_Model = glm::rotate(m_Model, angleInRadians, axis);
	}

	const glm::vec3& Object::GetPos()
	{
		return m_Position;
	}

	void Object::SetPos(glm::vec3 const& pos)
	{
		m_Position = pos;
	}

	void Object::SetPos(float const& x, float const& y, float const& z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}

	const glm::mat4& Object::GetModelMatrix()
	{
		return m_Model;
	}

	const glm::mat4& Object::GetNormalMatrix()
	{
		return glm::transpose(glm::inverse(m_Model));
	}
}