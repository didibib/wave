#pragma once

#include "scene/object/object.h"

namespace Wave
{
	class Camera : public Object
	{
	public:
		Camera() = delete;
		Camera(float const& fov, int const& viewWidth, int const& viewHeight, float const& near, float const& far);
		void Move(const Direction& dir, float const& deltaTime);
		void Cursor(float xOffset, float yOffset);
		glm::mat4 GetProjMatrix() { return m_Projection; }
		// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
		glm::mat4 GetViewMatrix();
		void OnWindowResize(int const& width, int const& height);
	private:
		void UpdateCameraVectors();
	private:
		float m_Fov;
		float m_Near;
		float m_Far;
		int m_ViewWidth;
		int m_ViewHeight;
	private:
		float m_Yaw;
		float m_Pitch;
	private:
		float m_MoveSpeed = 10;
		float m_MouseSensivity = 0.5f;
	private:
		glm::mat4 m_Projection;
	};
}