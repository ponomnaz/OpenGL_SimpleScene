#pragma once

#include "common_includes.h"
#include "SkyBoxShader.h"
#include "Object.h"

class SkyBox
{
public:
	SkyBox(SkyBoxShader* shader, std::string file);
	~SkyBox();


	bool loadModel();

	void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const float sunIntensity);

private:
	std::string MODEL_FILE_PATH;

	SkyBoxShader* shader;

	ObjectGeometry* geometry;
};