#version 330

in vec3 out_color;
in vec2 out_uv;

out vec4 frag_color;

uniform sampler2D texture1;

void main()
{
    frag_color = texture(texture1, out_uv);   
}