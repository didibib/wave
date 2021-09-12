#pragma once

#include "pch/wavepch.h"

namespace Wave
{
	class Cube
	{
	public:
		static const std::vector<Vertex> GetVertices()
		{
			// Order of vertices
			//  2 ___3,4
			//	 |  /|
			//	 | / |
			//   |/__|
			// 1,6    5

			static std::vector<Vertex> vertices = {
				// Front
				{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)},
				{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 1.0f)},
				{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},
				{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},
				{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 0.0f)},
				{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)},
				// Back
				{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)},
				{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 1.0f)},
				{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},
				{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},
				{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 0.0f)},
				{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)},
				// Left
				{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)},	
				{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 1.0f)},	
				{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},	
				{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},	
				{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 0.0f)},	
				{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)},	
				// Right
				{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)},	
				{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 1.0f)},	
				{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},	
				{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},	
				{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 0.0f)},	
				{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)},
				// Top
				{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)},
				{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 1.0f)},
				{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},
				{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},
				{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 0.0f)},
				{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)},
				// Bottom
				{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)},
				{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 1.0f)},
				{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},
				{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 1.0f)},
				{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(1.0f, 0.0f)},
				{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f), glm::vec2(0.0f, 0.0f)}
			};
			return vertices;
		}
	};
}