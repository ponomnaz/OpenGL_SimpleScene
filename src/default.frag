#version 460 core

struct Material {
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    float shininess;

    bool  useTexture;
    bool useTexture_2;
};

struct Light {
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    vec3  position;
};

smooth in vec3 fragmentPosition_v;
smooth in vec3 fragmentNormal_v;

out vec4 fragColor;

uniform Material material;
uniform mat4 view;


Light sun;

void setupLights() {
    sun.ambient = vec3(0.1f);
    sun.diffuse = vec3(1.0, 1.0, 0.8f);
    sun.specular = vec3(1.0, 1.0, 0.8f);
    sun.position = (view * vec4(0.0, 0.0, 10.0, 0.0)).xyz;
}

vec4 directionalLight(Light light, Material material, vec3 fragmentPosition, vec3 fragmentNormal) {

    vec3 outputColor = vec3(0.0);

    vec3 L = normalize(light.position);
    vec3 R = reflect(-L, fragmentNormal);
    vec3 V = normalize(-fragmentPosition);
    float NdotL = max(0.0, dot(fragmentNormal, L));
    float RdotV = max(0.0, dot(R, V));

    outputColor += material.ambient * light.ambient;
    outputColor += material.diffuse * light.diffuse * NdotL;
    outputColor += material.specular * light.specular * pow(RdotV, material.shininess);

    return vec4(outputColor, 1.0);
}

void main()
{
    setupLights();
    vec3 globalAmbientLight = vec3(0.1);
    fragColor = vec4(material.ambient * globalAmbientLight, 0.0);

    fragColor += directionalLight(sun, material, fragmentPosition_v, fragmentNormal_v);
}