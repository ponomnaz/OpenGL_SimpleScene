#pragma once

#include "common_includes.h"

/**
 * @class ElementBufferObject
 * @brief Manages an OpenGL Element Buffer Object (EBO).
 *
 * An EBO (also known as an Index Buffer Object) stores indices that define
 * how vertices should be connected to form primitives like triangles or quads.
 */
class ElementBufferObject {
public:
	/**
	 * @brief Constructs an Element Buffer Object (EBO).
	 * @param size The size (in bytes) of the index data.
	 * @param indices Pointer to the index data to be stored in the EBO.
	 */
	ElementBufferObject(GLsizeiptr size, const void* indices);
	
	/**
	* @brief Destroys the EBO and frees OpenGL resources.
	*/
	~ElementBufferObject();

	///< OpenGL buffer ID.
	GLuint ID;

	/**
	 * @brief Binds the EBO for use in rendering.
	 */
	void bind();

	/**
	 * @brief Unbinds the EBO to prevent unintended modifications.
	 */
	void unbind();
};

