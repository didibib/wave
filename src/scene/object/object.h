#pragma once

namespace Wave
{
	class Object
	{
	public:
		Object();
		void Translate(glm::vec3 translation);
		void Rotate(float angleInRadians, glm::vec3 axis);
		const glm::vec3& GetPos();
		void SetPos(glm::vec3 const& pos);
		void SetPos(float const& x, float const& y, float const& z);
		const glm::mat4& GetModelMatrix();
		const glm::mat4& GetNormalMatrix();

	private:
		glm::vec3 m_Position;
		glm::vec3 m_WorldUp;
		glm::mat4 m_Model;
	};
}