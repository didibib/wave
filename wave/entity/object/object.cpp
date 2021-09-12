#include "pch/wavepch.h"
#include "object.h"

namespace Wave
{
	Object::Object(glm::vec3 pos) 
		: mForward(0.f, 0.f, -1.f), mUp(0.f, 1.f, 0.f), mRight(1.f, 0.f, 0.f), mWorldUp(0.f, 1.f, 0.f)
	{
		SetPosition(pos);
	}

	void Object::SetPosition(glm::vec3 pos)
	{
		mPosition = pos;
	}

	void Object::SetPosition(float x, float y, float z)
	{
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;
	}
}


