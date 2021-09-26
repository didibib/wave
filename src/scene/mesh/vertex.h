#pragma once

// Include in the pch/wavepch.h

namespace Wave
{
	struct Vertex
	{
		glm::vec3 Position;		// 3 * float = 12 bytes
		glm::vec4 Color;		// 4 * float = 16 bytes
		glm::vec2 UV;			// 2 * float = 8  bytes
		glm::vec3 Normal;		// 3 * float = 12 bytes
	};
}