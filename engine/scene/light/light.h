#pragma once

#include "scene/object/object.h"

namespace Wave
{
	class Light : public Object
	{
	public:
		Light();
		Light(const glm::vec3& ambient, const glm::vec3& diffuse);
		const glm::vec3& GetAmbient() { return m_Ambient; }
		const glm::vec3& GetDiffuse() { return m_Diffuse; }
		const glm::vec3& GetSpecular() { return m_Specular; }
		void SetDiffuse(const glm::vec3& color);
		void SetDiffuse(const float& r, const float& g, const float& b);
	private:
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
	};
}