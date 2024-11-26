#pragma once

#include "common_includes.h"

class Shader
{
public:
	unsigned int program;

	struct {
		GLint position;
		GLint normal;

		GLint model;
		GLint view;
		GLint projection;

		GLint PVM;
		GLint normalMatrix;

		GLint diffuse;
		GLint ambient;
		GLint specular;
		GLint shininess;
	} locations;

	Shader();
	~Shader();

	virtual void createProgram(const std::string vertexFile, const std::string fragmentFile);

	virtual void setUp(void);

	void useProgram();

	void notUseProgram();

	void setMatrices(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

	void setMaterial(const glm::vec3& diffuse, const glm::vec3& ambient, const glm::vec3& specular, const float shininess);

private:
	virtual unsigned int createShader(const std::string& filePath, unsigned int shaderType);
};