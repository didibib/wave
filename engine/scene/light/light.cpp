#include "pch/wavepch.h"
#include "scene/object/object.h"
#include "light.h"

namespace Wave
{
	Light::Light() : Object(),
		m_Ambient(0.2f), m_Diffuse(0.5f), m_Specular(1.f)
	{
	}

	Light::Light(const glm::vec3& ambient, const glm::vec3& diffuse)
		: Object(), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(1.f)
	{
	}

	void Light::SetDiffuse(const glm::vec3& color)
	{
		m_Diffuse = color;
	}

	void Light::SetDiffuse(const float& r, const float& g, const float& b)
	{
		m_Diffuse.r = r;
		m_Diffuse.g = g;
		m_Diffuse.b = b;
	}
}