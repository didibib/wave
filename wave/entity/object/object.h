#pragma once

namespace Wave
{
	class Object
	{
	public:
		Object();
		Object(glm::vec3 pos);
		glm::vec3 GetPos() { return mPosition; }
		void SetPos(glm::vec3 pos);
		void SetPos(float x, float y, float z);
	protected:
		glm::vec3 mPosition;
		glm::vec3 mForward;
		glm::vec3 mUp;
		glm::vec3 mRight;
		glm::vec3 mWorldUp;
		glm::mat4 mModel;
	private:
	};
}