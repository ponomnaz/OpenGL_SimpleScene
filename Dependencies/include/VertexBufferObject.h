#pragma once

#include "common_includes.h"

class VertexBufferObject {
public:
	VertexBufferObject(GLsizeiptr size, const void* vertices);
	~VertexBufferObject();

	GLuint ID;

	void bind();

	void unbind();
};

