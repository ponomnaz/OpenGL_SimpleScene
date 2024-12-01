#include "ElementBufferObject.h"

ElementBufferObject::ElementBufferObject(GLsizeiptr size, const void* indices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

ElementBufferObject::~ElementBufferObject()
{
	glDeleteBuffers(1, &ID);
}

void ElementBufferObject::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ElementBufferObject::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}