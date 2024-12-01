#version 460 core

in vec3 position;
in vec3 normal;
in vec2 textureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 PVM;
uniform mat4 normalMatrix;

smooth out vec3 fragmentPosition_v;
smooth out vec3 fragmentNormal_v;
smooth out vec2 texCoord_v;

void main()
{
	fragmentPosition_v = (view * model * vec4(position, 1.0)).xyz;
	fragmentNormal_v = normalize((view * normalMatrix * vec4(normal, 0.0)).xyz);
	texCoord_v = textureCoord;
	gl_Position = PVM * vec4(position, 1.0);
}