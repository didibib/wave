#pragma once 

// Included in the pch/wavepch.h

namespace Wave
{
	struct Texture
	{
		GLuint Id = 0;
		std::string Type;
		uint Width = 0;
		uint Height = 0;
	};
}