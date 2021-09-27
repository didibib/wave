#pragma once

namespace Wave
{
	// Some usefull info about the camera matrices
	// https://gamedev.stackexchange.com/questions/178643/the-view-matrix-finally-explained

	class Camera
	{
	public:
		Camera() = delete;
		Camera(const float& fov, const int& viewWidth, const int& viewHeight, const float& near, const float& far);
		glm::vec3 GetPos();
		void SetPos(glm::vec3 const& pos);
		void SetPos(float const& x, float const& y, float const& z);
		glm::mat4 GetProjMatrix();
		// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
		glm::mat4 GetViewMatrix();
		glm::vec3 GetForward();
	public:
		void Move(const Direction& dir, const float& deltaTime);
		void Cursor(float xOffset, float yOffset);
		void OnWindowResize(const int& width, const int& height);
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
		glm::vec3 m_Position;
		glm::vec3 m_Forward;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;
		glm::mat4 m_Projection;
	};
}