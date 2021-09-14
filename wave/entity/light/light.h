#pragma once

#include "entity/object/object.h"

namespace Wave
{
	class Light : public Object
	{
	public:
		Light();
		Light(glm::vec3 position, glm::vec3 color, float strength);
		glm::vec3 GetColor() { return mColor; }
		float GetStrength() { return mStrength; }
		void SetColor(glm::vec3 color) { mColor = color; }
		void SetColor(float r, float g, float b) { mColor.r = r;  mColor.g = g; mColor.b = b; }
		void SetStrength(float strength) { mStrength = strength; }

	private:
		glm::vec3 mColor;
		float mStrength;
	};
}