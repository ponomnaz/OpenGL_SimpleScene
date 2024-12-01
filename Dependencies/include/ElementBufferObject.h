#pragma once

#include "common_includes.h"

class ElementBufferObject {
public:
	ElementBufferObject(GLsizeiptr size, const void* indices);
	~ElementBufferObject();

	GLuint ID;

	void bind();

	void unbind();
};

