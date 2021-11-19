#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;        
    float cutOff;
    float outerCutOff;  
    float constant;
    float linear;
    float quadratic;   
};

in vec4 Color;
in vec2 Uv;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 u_ViewPosition;
uniform Material u_Material;
uniform DirLight u_DirLight;
uniform SpotLight u_SpotLight;
#define NR_POINT_LIGHTS 4  
uniform PointLight u_PointLights[NR_POINT_LIGHTS];

vec3 CalcDirLight(DirLight _light, vec3 _normal, vec3 _viewDir);
vec3 CalcPointLight(PointLight _light, vec3 _normal, vec3 _viewDir, vec3 _fragPos);
vec3 CalcSpotLight(SpotLight _light, vec3 _normal, vec3 _viewDir, vec3 _fragPos);

void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(u_ViewPosition - FragPos);

    vec3 result = CalcDirLight(u_DirLight, normal, viewDir);
    result = CalcSpotLight(u_SpotLight, normal, viewDir, FragPos);

    for(int i = 0; i < NR_POINT_LIGHTS; i++){
        result += CalcPointLight(u_PointLights[i], normal, viewDir, FragPos);
    }

    FragColor = vec4(result, 1.0);  
}

vec3 CalcDirLight(DirLight _light, vec3 _normal, vec3 _viewDir){
    vec3 lightDir = normalize(-_light.direction);
    // Diffuse
    vec3 diffuseMap = texture(u_Material.diffuse, Uv).rgb;
    float diff = max(dot(_normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, _normal);
    float spec = pow(max(dot(_viewDir, reflectDir), 0.0), u_Material.shininess);
    // Combine
    vec3 ambient = _light.ambient * diffuseMap;
    vec3 diffuse = _light.diffuse * diff * diffuseMap;
    vec3 specular = _light.specular * spec * texture(u_Material.specular, Uv).rgb;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight _light, vec3 _normal, vec3 _viewDir, vec3 _fragPos){
    vec3 lightDir = normalize(_light.position - _fragPos);
    // Diffuse
    vec3 diffuseMap = texture(u_Material.diffuse, Uv).rgb;
    float diff = max(dot(_normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, _normal);
    float spec = pow(max(dot(_viewDir, reflectDir), 0.0), u_Material.shininess);
    // Attenuation
    float distance = distance(FragPos, _light.position);
    float attenuation = 1.0 / (_light.constant + _light.linear * distance + 
        _light.quadratic * (distance * distance));    
    // Combine
    vec3 ambient = _light.ambient * diffuseMap;
    vec3 diffuse = _light.diffuse * diff * diffuseMap;
    vec3 specular = _light.specular * spec * texture(u_Material.specular, Uv).rgb;
    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(SpotLight _light, vec3 _normal, vec3 _viewDir, vec3 _fragPos)
{
    vec3 lightDir = normalize(_light.position - _fragPos);
    // Diffuse
    float diff = max(dot(_normal, lightDir), 0.0);
    // Specular 
    vec3 reflectDir = reflect(-lightDir, _normal);
    float spec = pow(max(dot(_viewDir, reflectDir), 0.0), u_Material.shininess);
    // Attenuation
    float distance = length(_light.position - _fragPos);
    float attenuation = 1.0 / (_light.constant + _light.linear * distance + 
        _light.quadratic * (distance * distance));    
    // Intensity
    float theta = dot(lightDir, normalize(-_light.direction)); 
    float epsilon = _light.cutOff - _light.outerCutOff;
    float intensity = clamp((theta - _light.outerCutOff) / epsilon, 0.0, 1.0);
    // Combine
    vec3 ambient = _light.ambient * vec3(texture(u_Material.diffuse, Uv));
    vec3 diffuse = _light.diffuse * diff * vec3(texture(u_Material.diffuse, Uv));
    vec3 specular = _light.specular * spec * vec3(texture(u_Material.specular, Uv));
    return (ambient + diffuse + specular) * attenuation * intensity;
}