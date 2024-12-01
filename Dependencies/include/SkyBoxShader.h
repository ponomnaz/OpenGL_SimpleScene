#pragma once
#include "Shader.h"

class SkyBoxShader : public Shader 
{
public:

	struct {
		GLint coord;
		GLint inversePV;
		GLint sampler;
		GLint cameraPosition;
	} locations;

	SkyBoxShader();

	void setUp(void) override;

	void setUniforms(const glm::mat4 inversePV, const glm::vec3 cameraPosition);
};