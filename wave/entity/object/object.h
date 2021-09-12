#pragma once

namespace Wave
{
	class Object
	{
	public:
		Object(glm::vec3 pos);
		void SetPosition(glm::vec3 pos);
		void SetPosition(float x, float y, float z);
	protected:
		glm::vec3 mPosition;
		glm::vec3 mForward;
		glm::vec3 mUp;
		glm::vec3 mRight;
		glm::vec3 mWorldUp;
	protected:
		glm::mat4 mModel;
	};
}