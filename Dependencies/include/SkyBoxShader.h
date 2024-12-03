#pragma once
#include "Shader.h"

class SkyBoxShader : public Shader 
{
public:

	struct {
		GLint coord;
		GLint inversePV;
		GLint sampler;
		GLint sunIntensity;
	} locations;

	SkyBoxShader();

	void setUp(void) override;

	void setUniforms(const glm::mat4 inversePV, const float intensity);
};