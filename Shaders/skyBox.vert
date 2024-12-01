#version 460 core


in vec2 coord;
out vec3 coordVertex;

uniform mat4 inversePV;

void main() {
    vec4 farplane = vec4(coord, 0.9999, 1.0);
    vec4 worldView = inversePV * farplane;
    coordVertex = worldView.xyz / worldView.w;
    gl_Position = farplane;
}