#pragma once

#include "common_includes.h"
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"
#include "VertexBufferObject.h"

class ObjectGeometry {
public:

	VertexBufferObject* VBO = nullptr;
	ElementBufferObject* EBO = nullptr;
	VertexArrayObject* VAO = nullptr;
	unsigned int numTriangles;
	glm::vec3 diffuse;
	glm::vec3 ambient;
	glm::vec3 specular;
	float shininess;
	GLuint texture;

	ObjectGeometry() {}
	~ObjectGeometry() {
		delete VBO;
		delete EBO;
		delete VAO;
	}
};

