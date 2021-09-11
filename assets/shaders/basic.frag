#version 330 core

in vec4 vert_color;
in vec2 vert_uv;

out vec4 frag_color;

uniform sampler2D texture1;

void main()
{
    frag_color = texture(texture1, vert_uv);  
}