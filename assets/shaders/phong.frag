#version 410 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float strength;
};

in vec4 Color;
in vec2 Uv;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 u_ViewPosition;
uniform Material u_Material;
uniform Light u_Light;

void main()
{
    vec3 diffuseMap = texture(u_Material.diffuse, Uv).rgb;

    // Ambient
    vec3 ambient = u_Light.ambient * diffuseMap;

    // Diffuse
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(u_Light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = u_Light.diffuse * diff * diffuseMap;

    // Spec
    vec3 viewDir = normalize(u_ViewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float shine = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    vec3 specularMap = texture(u_Material.specular, Uv).rgb;
    vec3 specular = u_Light.specular * shine * specularMap; 

    // Emission
    vec3 emissionMask = step(vec3(1.0), vec3(1.0)-specularMap);
    vec3 emission = texture(u_Material.emission, Uv).rgb * emissionMask;

    // Result
    float dist = distance(FragPos, u_Light.position);
    float strengthFallOf = u_Light.strength / dist;
    vec3 result = (ambient + diffuse + specular) * strengthFallOf + emission;
    FragColor = vec4(result, 1.0);  
}