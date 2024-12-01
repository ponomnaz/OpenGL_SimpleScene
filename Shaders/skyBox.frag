#version 460 core


in vec3 coordVertex;
out vec4 fragmentColor;

uniform samplerCube sampler;

void main() {
    fragmentColor = texture(sampler, coordVertex);
}