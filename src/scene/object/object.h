#pragma once

namespace Wave
{
	class Object
	{
	public:
		Object();
		glm::vec3 GetPos() { return m_Position; }
		void SetPos(glm::vec3 const& pos);
		void SetPos(float const& x, float const& y, float const& z);
		glm::vec3 GetForward() { return m_Forward; }
	protected:
		glm::vec3 m_Position;
		glm::vec3 m_Forward;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;
		glm::mat4 m_Model;
	};
}