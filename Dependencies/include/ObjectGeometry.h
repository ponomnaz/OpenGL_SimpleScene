#pragma once

#include "common_includes.h"
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"
#include "VertexBufferObject.h"

/**
 * @class ObjectGeometry
 * @brief Represents the geometry of an object, including its buffers, material properties, and texture.
 *
 * This class encapsulates the vertex data (VBO), index data (EBO), and vertex array object (VAO)
 * for a 3D object. It also contains material properties like diffuse, ambient, specular colors,
 * and shininess, as well as a texture for rendering.
 */
class ObjectGeometry {
public:
    VertexBufferObject* VBO = nullptr; ///< Pointer to the vertex buffer object storing vertex data.
    ElementBufferObject* EBO = nullptr; ///< Pointer to the element buffer object storing index data.
    VertexArrayObject* VAO = nullptr;  ///< Pointer to the vertex array object which links buffers.

    unsigned int numTriangles; ///< Number of triangles in the object’s geometry.

    glm::vec3 diffuse;  ///< Diffuse material color.
    glm::vec3 ambient;  ///< Ambient material color.
    glm::vec3 specular; ///< Specular material color.
    float shininess;    ///< Shininess coefficient for the material.

    GLuint texture;     ///< Texture ID applied to the object, if any.

    /**
     * @brief Default constructor.
     *
     * Initializes the pointers to `nullptr`, and material properties to default values.
     */
    ObjectGeometry() {}

    /**
     * @brief Destructor.
     *
     * Deletes the dynamically allocated VBO, EBO, and VAO to release OpenGL resources.
     */
    ~ObjectGeometry() {
        delete VBO;
        delete EBO;
        delete VAO;
    }
};
