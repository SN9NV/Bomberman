#version 330 core

in vec3	fragmentNormal;
in vec2	fragmentUV;
in vec3 frsgmrntPosition;

out vec4 colour;

uniform sampler2D   samplerUV;
uniform vec3        cameraPosition;


vec3 CalcDirLight(vec3 direction, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 diffuse  = vec3(0.8, 0.8, 0.8)  * diff;
    vec3 specular = vec3(0.5, 0.5, 0.5) * spec ;
    return (diffuse + specular);
}

void main() {
    const vec3 directionLight = vec3(0, -2, 1);
    const float ambientStrength = 0.4;

    vec3 ambient = ambientStrength * vec3(1,1,1);
    vec3 Normal = normalize(fragmentNormal);
    vec3 viewDir = normalize(cameraPosition - frsgmrntPosition);
    vec3 combind = ambient  + CalcDirLight(directionLight, Normal, viewDir);

	colour = vec4(combind, 1) * texture(samplerUV, fragmentUV);
}