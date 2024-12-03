#version 460 core

struct Material {
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    float shininess;

    bool  useTexture;
};

struct Sun {
    vec3 position;

    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    vec3 globalAmbientLight;
};

smooth in vec3 fragmentPosition_v;
smooth in vec3 fragmentNormal_v;
smooth in vec2 texCoord_v;

out vec4 fragmentColor;

uniform Material material;
uniform Sun sun;
uniform mat4 view;
uniform sampler2D texture;

vec4 directionalLight(Sun sun, mat4 view, Material material, vec3 fragmentPosition, vec3 fragmentNormal) {

    vec3 outputColor = vec3(0.0);

    vec3 L = normalize((view * vec4(sun.position, 0.0)).xyz);
    vec3 R = reflect(-L, fragmentNormal);
    vec3 V = normalize(-fragmentPosition);
    float NdotL = max(0.0, dot(fragmentNormal, L));
    float RdotV = max(0.0, dot(R, V));

    outputColor += material.ambient * sun.ambient;
    outputColor += material.diffuse * sun.diffuse * NdotL;
    outputColor += material.specular * sun.specular * pow(RdotV, material.shininess);

    return vec4(outputColor, 1.0);
}

void main()
{
    fragmentColor = vec4(material.ambient * sun.globalAmbientLight, 0.0);

    fragmentColor += directionalLight(sun, view, material, fragmentPosition_v, fragmentNormal_v);

    if (material.useTexture) {
        fragmentColor *= texture(texture, texCoord_v);
    }
}