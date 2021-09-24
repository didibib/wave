#include "pch/wavepch.h"
#include "light.h"

namespace Wave
{
	Light::Light() : Object(),
		m_Ambient(0.2f), m_Diffuse(0.5f), m_Specular(1.f)
	{
	}

	Light::Light(glm::vec3 const& ambient, glm::vec3 const& diffuse)
		: Object(), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(1.f)
	{
	}

	void Light::SetDiffuse(glm::vec3 const& color) 
	{ 
		m_Diffuse = color; 
	}

	void Light::SetDiffuse(float const& r, float const& g, float const& b) 
	{ 
		m_Diffuse.r = r;  
		m_Diffuse.g = g; 
		m_Diffuse.b = b; 
	}
}