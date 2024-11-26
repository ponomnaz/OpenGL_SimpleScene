#pragma once

#include "common_includes.h"

class VertexArrayObject {
public:
	VertexArrayObject();
	~VertexArrayObject();

	GLuint ID;

	void LinkAttributes(GLuint layout, GLuint numComponents, GLuint type, GLsizeiptr stride, void* offset);

	void Bind();

	void Unbind();
};

