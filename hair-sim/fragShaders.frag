#version 330 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 fragColor;

void main()
{
    // Lighting calculations
    vec3 ambientColor = vec3(0.1, 0.1, 0.1);
    vec3 diffuseColor = vec3(0.8, 0.8, 0.8);
    vec3 specularColor = vec3(1.0, 1.0, 1.0);
    float shininess = 32.0;

    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 normal = normalize(fragNormal);

    vec3 ambient = ambientColor;
    vec3 diffuse = diffuseColor * max(dot(normal, lightDir), 0.0);
    vec3 specular = specularColor * pow(max(dot(reflect(-lightDir, normal), viewDir), 0.0), shininess);

    fragColor = vec4(ambient + diffuse + specular, 1.0);
}
