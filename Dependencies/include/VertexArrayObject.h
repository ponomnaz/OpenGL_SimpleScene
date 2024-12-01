#pragma once

#include "common_includes.h"

class VertexArrayObject {
public:
	VertexArrayObject();
	~VertexArrayObject();

	GLuint ID;

	void linkAttributes(GLuint layout, GLuint numComponents, GLuint type, GLsizeiptr stride, void* offset);

	void bind();

	void unbind();
};

