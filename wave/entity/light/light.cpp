#include "pch/wavepch.h"
#include "light.h"

namespace Wave
{
	Light::Light() : 
		mColor({ 1.f, 1.f, 1.f }), mStrength(5)
	{
	}

	Light::Light(glm::vec3 position, glm::vec3 color, float strength)
	{
		mPosition = position;
		mColor = color;
		mStrength = strength;
	}

}