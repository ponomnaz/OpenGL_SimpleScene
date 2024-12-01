#pragma once

#include "common_includes.h"

class Shader
{
public:
	GLuint program;

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
		GLint textureCoord;
		GLint texture;
		GLint useTexture;
	} locations;

	Shader();
	virtual ~Shader();

	virtual void createProgram(const std::string vertexFile, const std::string fragmentFile);

	virtual void setUp(void);

	void useProgram(const bool use);

	virtual void setMatrices(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

	virtual void setMaterial(const glm::vec3& diffuse, const glm::vec3& ambient, const glm::vec3& specular, const float shininess, const GLuint texture);

private:
	virtual unsigned int createShader(const std::string& filePath, const unsigned int shaderType);
};