#pragma once

#include "scene/object/object.h"

namespace Wave
{
	class Light : public Object
	{
	public:
		Light();
		Light(glm::vec3 const& ambient, glm::vec3 const& diffuse);
		glm::vec3 GetAmbient() { return m_Ambient; }
		glm::vec3 GetDiffuse() { return m_Diffuse; }
		glm::vec3 GetSpecular() { return m_Specular; }
		void SetDiffuse(glm::vec3 const& color);
		void SetDiffuse(float const& r, float const& g, float const& b);
	private:
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
	};
}