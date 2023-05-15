#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Tangent;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D textureSampler;

void main()
{
    // Calculate the tangent space basis
    vec3 T = normalize(Tangent - dot(Tangent, Normal) * Normal);
    vec3 B = cross(Normal, T);

    // Calculate the surface normal in tangent space
    mat3 TBN = mat3(T, B, Normal);
    vec3 normalMap = texture(textureSampler, TexCoords).rgb;
    vec3 normal = normalize(TBN * (normalMap * 2.0 - 1.0));

    // Calculate the diffuse lighting
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuseStrength = max(dot(normal, lightDir), 0.0);

    // Calculate the specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    // Combine the diffuse and specular lighting
    vec3 ambient = 0.1 * vec3(1.0, 1.0, 1.0);
    vec3 diffuse = 0.8 * diffuseStrength * vec3(1.0, 1.0, 1.0);
    vec3 specular = 0.5 * specularStrength * vec3(1.0, 1.0, 1.0);
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}