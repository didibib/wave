#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_Uv;
layout (location = 3) in vec3 a_Normal;

void main()
{
   gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
}