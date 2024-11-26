#pragma once

#include "common_includes.h"

class VertexBufferObject {
public:
	VertexBufferObject(GLsizeiptr size, const void* vertices);
	~VertexBufferObject();

	GLuint ID;

	void LinkAttributes(GLuint layout, GLuint numComponents, GLuint type, GLsizeiptr stride, void* offset);

	void Bind();

	void Unbind();
};

