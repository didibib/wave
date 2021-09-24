#pragma once 

// Included in the pch/wavepch.h

namespace Wave
{
	struct Texture
	{
		enum class Type { Diffuse, Specular, Height };
		GLuint Id = 0;
		uint Width = 0;
		uint Height = 0;
	};
}