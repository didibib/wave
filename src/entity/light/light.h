#pragma once

#include "entity/object/object.h"

namespace Wave
{
	class Light : public Object
	{
	public:
		Light();
		Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, float strength);
		glm::vec3 GetAmbient() { return m_Ambient; }
		glm::vec3 GetDiffuse() { return m_Diffuse; }
		glm::vec3 GetSpecular() { return m_Specular; }
		float GetStrength() { return m_Strength; }
		void SetDiffuse(glm::vec3 color) { m_Diffuse = color; }
		void SetDiffuse(float r, float g, float b) { m_Diffuse.r = r;  m_Diffuse.g = g; m_Diffuse.b = b; }
		void SetStrength(float strength) { m_Strength = strength; }

	private:
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
		float m_Strength;
	};
}