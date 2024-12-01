#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(GLsizeiptr size, const void* vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &ID);
}

void VertexBufferObject::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBufferObject::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}