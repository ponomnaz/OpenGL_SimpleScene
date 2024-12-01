#include "Shader.h"
#include <windows.h>

Shader::Shader()
{
	program = 0;


	locations.position = -1;
	locations.normal = -1;
	locations.model = -1;
	locations.view = -1;
	locations.projection = -1;
	locations.PVM = -1;
	locations.normalMatrix = -1;

	locations.diffuse = -1;
	locations.ambient = -1;
	locations.specular = -1;
	locations.shininess = -1;

	locations.textureCoord = -1;
	locations.texture = -1;
	locations.useTexture = -1;
}

Shader::~Shader() {
	glDeleteProgram(program);
}

void Shader::createProgram(const std::string vertexFile, const std::string fragmentFile) {
	std::vector<unsigned int> shaders;

	shaders.push_back(createShader(vertexFile, GL_VERTEX_SHADER));
	shaders.push_back(createShader(fragmentFile, GL_FRAGMENT_SHADER));

	
	program = glCreateProgram();
	for (unsigned int shaderModule : shaders) {
		glAttachShader(program, shaderModule);
	}
	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetProgramInfoLog(program, 1024, NULL, errorLog);
		std::cout << "Shader linking error:\n" << errorLog << '\n';
	}

	for (unsigned int shaderModule : shaders) {
		glDeleteShader(shaderModule);
	}
}

unsigned int Shader::createShader(const std::string& filePath, const unsigned int shaderType) {
	std::ifstream file;
	std::stringstream bufferedLines;
	std::string line;

	file.open(filePath);

	if (!file.is_open()) {
		std::cerr << "Failed to open file " << filePath << std::endl;
		return 1;
	}

	while (std::getline(file, line)) {
		bufferedLines << line << '\n';
	}
	std::string shaderSource = bufferedLines.str();
	const char* shaderSrc = shaderSource.c_str();
	bufferedLines.str("");
	file.close();

	unsigned int shaderModule = glCreateShader(shaderType);
	glShaderSource(shaderModule, 1, &shaderSrc, NULL);
	glCompileShader(shaderModule);

	int success;
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
		std::cout << "Shader Module compilation error:\n" << errorLog << std::endl;
	}

	return shaderModule;
}

void Shader::setUp(void) {
	locations.position = glGetAttribLocation(program, "position");
	locations.normal = glGetAttribLocation(program, "normal");
	locations.textureCoord = glGetAttribLocation(program, "textureCoord");

	locations.model = glGetUniformLocation(program, "model");
	locations.view = glGetUniformLocation(program, "view");
	locations.projection = glGetUniformLocation(program, "projection");

	locations.PVM = glGetUniformLocation(program, "PVM");
	locations.normalMatrix = glGetUniformLocation(program, "normalMatrix");

	locations.diffuse = glGetUniformLocation(program, "material.diffuse");
	locations.ambient = glGetUniformLocation(program, "material.ambient");
	locations.specular = glGetUniformLocation(program, "material.specular");
	locations.shininess = glGetUniformLocation(program, "material.shininess");
	locations.texture = glGetUniformLocation(program, "material.texture");
	locations.useTexture = glGetUniformLocation(program, "material.useTexture");

	assert(locations.position != -1);
	assert(locations.normal != -1);
	assert(locations.model != -1);
	assert(locations.view != -1);
	assert(locations.projection != -1);
	assert(locations.PVM != -1);
	assert(locations.normalMatrix != -1);
	assert(locations.diffuse != -1);
	assert(locations.ambient != -1);
	assert(locations.specular != -1);
	assert(locations.shininess != -1);
	assert(locations.textureCoord != -1);
	assert(locations.texture != -1);
	assert(locations.useTexture != -1);
}

void Shader::useProgram(const bool use) {
	if (use)
		glUseProgram(program);
	else
		glUseProgram(0);
}

void Shader::setMatrices(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {	
	glUniformMatrix4fv(locations.model, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(locations.view, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(locations.projection, 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 PVM = projection * view * model;
	glUniformMatrix4fv(locations.PVM, 1, GL_FALSE, glm::value_ptr(PVM));

	const glm::mat4 modelRotationMatrix = glm::mat4(
		model[0],
		model[1],
		model[2],
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);

	glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelRotationMatrix));

	glUniformMatrix4fv(locations.normalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	
}

void Shader::setMaterial(const glm::vec3& diffuse, const glm::vec3& ambient, const glm::vec3& specular, const float shininess, const GLuint texture) {
	glUniform3fv(locations.diffuse, 1, glm::value_ptr(diffuse));
	glUniform3fv(locations.ambient, 1, glm::value_ptr(ambient));
	glUniform3fv(locations.specular, 1, glm::value_ptr(specular));
	glUniform1f(locations.shininess, shininess);

	if (texture != 0) {
		glUniform1i(locations.useTexture, 1);
		glUniform1i(locations.texture, 0);
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	else {
		glUniform1i(locations.useTexture, 0);
		std::cout << "No texture\n" << std::endl;
	}
}
