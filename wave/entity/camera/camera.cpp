#include "pch/wavepch.h"
#include "camera.h"

namespace Wave
{
	Camera::Camera(float fov, int viewWidth, int viewHeight, float near, float far) 
		// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector 
		// pointing to the right so we initially rotate a bit to the left.
		: Object({0, 0, 3}), mYaw(-90), mPitch(0)
	{
		mFov = fov;
		mViewWidth = viewWidth;
		mViewHeight = viewHeight;
		mNear = near;
		mFar = far;
		mProjection = glm::perspective(glm::radians(mFov), (float)mViewWidth / (float)mViewHeight, mNear, mFar);
		UpdateCameraVectors();
	}

	void Camera::Move(Direction dir, float deltaTime)
	{
		float velocity = mMoveSpeed * deltaTime;
		switch (dir)
		{
		case Direction::Forward:
			mPosition += mForward * velocity;
			break;
		case Direction::Backward:
			mPosition -= mForward * velocity;
			break;
		case Direction::Right:
			mPosition += mRight * velocity;
			break;
		case Direction::Left:
			mPosition -= mRight * velocity;
			break;
		case Direction::Up:
			mPosition += mUp * velocity;
			break;
		case Direction::Down:
			mPosition -= mUp * velocity;
			break;
		default:
			break;
		}
	}

	void Camera::Cursor(float xOffset, float yOffset)
	{
		xOffset *= mMouseSensivity;
		yOffset *= mMouseSensivity;
		mYaw = glm::mod(mYaw + xOffset, 360.f);
		mPitch += yOffset;
		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		mPitch = glm::clamp(mPitch, -89.f, 89.f);
		UpdateCameraVectors();
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(mPosition, mPosition + mForward, mUp);
	}

	void Camera::OnWindowResize(int width, int height)
	{
		if (width > 0 && height > 0)
		{
			mProjection = glm::perspective(glm::radians(mFov), (float)mViewWidth / (float)mViewHeight, mNear, mFar);
		}
	}

	void Camera::UpdateCameraVectors()
	{
		// Calculate the new mForward vector
		glm::vec3 forward;
		forward.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		forward.y = sin(glm::radians(mPitch));
		forward.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		mForward = glm::normalize(forward);
		// Also re-calculate the Right and Up vector
		// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		mRight = glm::normalize(glm::cross(mForward, mWorldUp));  
		mUp = glm::normalize(glm::cross(mRight, mForward));
	}
}