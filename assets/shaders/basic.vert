#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 uv;

out vec4 vert_color;
out vec2 vert_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = vec4(pos, 1.0);
    vert_color = vec4(col, 1.0);
    vert_uv = uv;
}