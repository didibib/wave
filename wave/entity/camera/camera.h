#pragma once

#include "entity/object/object.h"

namespace Wave
{
	class Camera : public Object
	{
	public:
		Camera() = delete;
		Camera(float fov, int viewWidth, int viewHeight, float near, float far);
		void Move(Direction dir, float deltaTime);
		void Cursor(float xOffset, float yOffset);
		glm::mat4 GetProjMatrix() { return mProjection; }
		// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
		glm::mat4 GetViewMatrix();
		void OnWindowResize(int width, int height);
	private:
		void UpdateCameraVectors();
	private:
		float mFov;
		float mNear;
		float mFar;
		int mViewWidth;
		int mViewHeight;
	private:
		float mYaw;
		float mPitch;
	private:
		float mMoveSpeed = 10;
		float mMouseSensivity = 0.5f;
	private:
		glm::mat4 mProjection;
	};
}