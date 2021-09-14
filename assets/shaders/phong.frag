#version 410 core

in vec4 Color;
in vec2 Uv;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform float lightStrength;
uniform vec3 viewPosition;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    // Placeholder so that the uniforms don't get removed
    vec4 tex = mix(texture(texture0, Uv), texture(texture1, Uv), 0.2);  

    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // View
    vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    // Spec
    float specularStrength = 0.5;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    vec3 specular = specularStrength * spec * lightColor; 

    // Result
    float dist = distance(FragPos, lightPosition);
    float strengthFallof = lightStrength / dist;
    vec3 result = (ambient + diffuse + specular) * objectColor * strengthFallof;
    FragColor = vec4(result, 1.0);  
}