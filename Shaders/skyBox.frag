#version 460 core


in vec3 coordVertex;
out vec4 fragmentColor;

uniform samplerCube sampler;
uniform float sunIntensity;

void main() {
    vec3 nightColor = vec3(0.0, 0.0, 0.0f);
    vec4 skyColor = texture(sampler, coordVertex);
    vec3 blendedColor = mix(skyColor.rgb, nightColor, 1.0f - sunIntensity);
    fragmentColor = vec4(blendedColor, skyColor.a);
}