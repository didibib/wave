#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;

out vec4 Color;
out vec2 Uv;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalMatrix;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    Color = vec4(color, 1.0);
    Uv = uv;
    Normal = mat3(normalMatrix) * normal;
    FragPos = vec3(model * vec4(position, 1.0));
}