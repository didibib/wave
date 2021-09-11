#include "pch/wavepch.h"
#include "camera.h"

namespace Wave
{
	Camera::Camera(int width, int height)
	{

	}

	void Camera::Move(Direction dir, float deltaTime)
	{
		float velocity = mSpeed * deltaTime;
		switch (dir)
		{
		case Direction::Forward:
			break;
		case Direction::Backward:
			break;
		case Direction::Left:
			break;
		case Direction::Right:
			break;
		case Direction::Up:
			break;
		case Direction::Down:
			break;
		default:
			break;
		}
	}

	void Camera::FollowPointer(float xOffset, float yOffset)
	{
	}
}