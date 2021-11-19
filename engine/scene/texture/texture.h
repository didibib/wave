#pragma once 

// Included in the pch/wavepch.h

namespace Wave
{
	struct Texture
	{
		Texture(GLuint id, TextureType type, std::string filepath, uint width, uint height)
			:Id(id), Type(type), Filepath(filepath), Width(width), Height(height)
		{			
		}

		GLuint Id = 0;
		TextureType Type;
		std::string Filepath;
		uint Width = 0;
		uint Height = 0;
	};
}