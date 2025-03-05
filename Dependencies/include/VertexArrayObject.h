#pragma once

#include "common_includes.h"

/**
 * @class VertexArrayObject
 * @brief Manages an OpenGL Vertex Array Object (VAO).
 *
 * A VAO stores the configuration of vertex attributes, which allows OpenGL to
 * quickly switch between different vertex data setups when rendering.
 */
class VertexArrayObject {
public:
	/**
	 * @brief Constructs a Vertex Array Object (VAO).
	 */
	VertexArrayObject();

	/**
	 * @brief Destroys the VAO and releases OpenGL resources.
	 */
	~VertexArrayObject();

	GLuint ID; ///< OpenGL ID for the VAO.

	/**
	 * @brief Links a vertex attribute to the VAO.
	 * @param layout The layout location in the shader.
	 * @param numComponents Number of components per vertex attribute (1-4).
	 * @param type Data type of the attribute (GL_FLOAT, GL_INT, etc.).
	 * @param stride Byte offset between consecutive vertex attributes.
	 * @param offset Pointer to the offset of the first component in the array.
	 */
	void linkAttributes(GLuint layout, GLuint numComponents, GLuint type, GLsizeiptr stride, void* offset);

	/**
	 * @brief Binds the VAO for use in rendering.
	 */
	void bind();

	/**
	 * @brief Unbinds the VAO to prevent unintended modifications.
	 */
	void unbind();
};

