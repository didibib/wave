#pragma once

namespace Wave
{
	class Camera
	{
	public:
		enum class Direction { Forward, Backward, Left, Right, Up, Down };
	public:
		Camera(int width, int height);
		void Move(Direction dir, float deltaTime);
		void FollowPointer(float xOffset, float yOffset);
	private:
		float mNear;
		float mFar;
		int mViewWidth;
		int mViewHeight;
	private:
		float mSpeed = 10;
		float mSensivity = 0.5f;
	};
}