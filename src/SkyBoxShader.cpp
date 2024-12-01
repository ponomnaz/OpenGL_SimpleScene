#include "SkyBoxShader.h"

SkyBoxShader::SkyBoxShader()
{
	program = 0;

	locations.coord = -1;
	locations.inversePV = -1;
	locations.sampler = -1;
	locations.cameraPosition = -1;
}

void SkyBoxShader::setUp(void) {
	locations.coord = glGetAttribLocation(program, "coord");
	locations.inversePV = glGetUniformLocation(program, "inversePV");
	locations.sampler = glGetUniformLocation(program, "sampler");
	locations.cameraPosition = glGetUniformLocation(program, "cameraPosition");

	assert(locations.coord != -1);
	assert(locations.inversePV != -1);
	assert(locations.sampler != -1);
	assert(locations.cameraPosition != -1);
}

void SkyBoxShader::setUniforms(const glm::mat4 inversePV, const glm::vec3 cameraPosition) {
	glUniformMatrix4fv(locations.inversePV, 1, GL_FALSE, glm::value_ptr(inversePV));
	glUniform1i(locations.sampler, 0);
	glUniform3fv(locations.cameraPosition, 1, glm::value_ptr(cameraPosition));
}