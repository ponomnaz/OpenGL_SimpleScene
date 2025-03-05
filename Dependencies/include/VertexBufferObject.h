#pragma once

#include "common_includes.h"

/**
 * @class VertexBufferObject
 * @brief Manages an OpenGL Vertex Buffer Object (VBO).
 *
 * A VBO stores vertex data (positions, colors, normals, etc.) in GPU memory,
 * enabling efficient rendering in OpenGL.
 */
class VertexBufferObject {
public:
	/**
	 * @brief Constructs a Vertex Buffer Object (VBO) and uploads vertex data to the GPU.
	 * @param size The size (in bytes) of the vertex data.
	 * @param vertices Pointer to the vertex data to be stored in the VBO.
	 */
	VertexBufferObject(GLsizeiptr size, const void* vertices);
	
	/**
	 * @brief Destroys the VBO and releases OpenGL resources.
	 */
	~VertexBufferObject();

	GLuint ID; ///< OpenGL ID for the VBO.

	/**
	 * @brief Binds the VBO for use in rendering.
	 */
	void bind();

	/**
	 * @brief Unbinds the VBO to prevent unintended modifications.
	 */
	void unbind();
};

