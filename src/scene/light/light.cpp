#include "pch/wavepch.h"
#include "light.h"

namespace Wave
{
	Light::Light() : 
		m_Ambient(0.2f), m_Diffuse(0.5f), m_Specular(1.f), m_Strength(5)
	{
	}

	Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, float strength)
		: m_Specular(1.f)
	{
		m_Position = position;
		m_Ambient = ambient;
		m_Diffuse = diffuse;
		m_Strength = strength;
	}
}