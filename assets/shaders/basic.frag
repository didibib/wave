#version 410 core

in vec4 VertColor;
in vec2 VertUv;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    FragColor = mix(texture(texture0, VertUv), texture(texture1, VertUv), 0.2);  
}