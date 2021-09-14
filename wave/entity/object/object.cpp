#include "pch/wavepch.h"
#include "object.h"

namespace Wave
{
	Object::Object() :
		mPosition(0.f, 0.f, 0.f), mForward(0.f, 0.f, -1.f), mUp(0.f, 1.f, 0.f), mRight(1.f, 0.f, 0.f), mWorldUp(0.f, 1.f, 0.f), mModel(1.f)
	{
	}

	Object::Object(glm::vec3 pos) : 
		mForward(0.f, 0.f, -1.f), mUp(0.f, 1.f, 0.f), mRight(1.f, 0.f, 0.f), mWorldUp(0.f, 1.f, 0.f), mModel(1.f)
	{
		SetPos(pos);
	}

	void Object::SetPos(glm::vec3 pos)
	{
		mPosition = pos;
	}

	void Object::SetPos(float x, float y, float z)
	{
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;
	}
}


