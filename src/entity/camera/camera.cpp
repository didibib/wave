#include "pch/wavepch.h"
#include "camera.h"

namespace Wave
{
	Camera::Camera(float fov, int viewWidth, int viewHeight, float near, float far) 
		// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector 
		// pointing to the right so we initially rotate a bit to the left.
		: Object({0, 0, 3}), m_Yaw(-90), m_Pitch(0)
	{
		m_Fov = fov;
		m_ViewWidth = viewWidth;
		m_ViewHeight = viewHeight;
		m_Near = near;
		m_Far = far;
		m_Projection = glm::perspective(glm::radians(m_Fov), (float)m_ViewWidth / (float)m_ViewHeight, m_Near, m_Far);
		UpdateCameraVectors();
	}

	void Camera::Move(Direction dir, float deltaTime)
	{
		float velocity = m_MoveSpeed * deltaTime;
		switch (dir)
		{
		case Direction::Forward:
			m_Position += m_Forward * velocity;
			break;
		case Direction::Backward:
			m_Position -= m_Forward * velocity;
			break;
		case Direction::Right:
			m_Position += m_Right * velocity;
			break;
		case Direction::Left:
			m_Position -= m_Right * velocity;
			break;
		case Direction::Up:
			m_Position += m_Up * velocity;
			break;
		case Direction::Down:
			m_Position -= m_Up * velocity;
			break;
		default:
			break;
		}
	}

	void Camera::Cursor(float xOffset, float yOffset)
	{
		xOffset *= m_MouseSensivity;
		yOffset *= m_MouseSensivity;
		m_Yaw = glm::mod(m_Yaw + xOffset, 360.f);
		m_Pitch += yOffset;
		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		m_Pitch = glm::clamp(m_Pitch, -89.f, 89.f);
		UpdateCameraVectors();
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
	}

	void Camera::OnWindowResize(int width, int height)
	{
		if (width > 0 && height > 0)
		{
			m_Projection = glm::perspective(glm::radians(m_Fov), (float)m_ViewWidth / (float)m_ViewHeight, m_Near, m_Far);
		}
	}

	void Camera::UpdateCameraVectors()
	{
		// Calculate the new mForward vector
		glm::vec3 forward;
		forward.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		forward.y = sin(glm::radians(m_Pitch));
		forward.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Forward = glm::normalize(forward);
		// Also re-calculate the Right and Up vector
		// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Right = glm::normalize(glm::cross(m_Forward, m_WorldUp));  
		m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
	}
}