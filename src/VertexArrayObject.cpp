#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &ID);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &ID);
}

void VertexArrayObject::LinkAttributes(GLuint layout, GLuint numComponents, GLuint type, GLsizeiptr stride, void* offset)
{
	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(ID);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}