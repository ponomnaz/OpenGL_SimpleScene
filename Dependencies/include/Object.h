#pragma once

#include "common_includes.h"
#include <IL/il.h>
#include "Camera.h"
#include "Shader.h"
#include "ObjectGeometry.h"

/**
 * @class Object
 * @brief Represents a 3D object in the scene, including its geometry, material, and transformation.
 *
 * The `Object` class manages the loading and rendering of 3D models, including their textures, geometry,
 * shaders, and transformations (position, size, rotation). It provides methods for updating and rendering
 * the object with appropriate transformations and material properties.
 */
class Object {
public:
    /**
     * @brief Constructs an Object instance with a given shader and model file path.
     * @param shader Pointer to the shader used for rendering the object.
     * @param path The file path to the model.
     */
    Object(Shader* shader, const std::string path);

    /**
     * @brief Destroys the Object and frees resources.
     */
    virtual ~Object();

    /**
     * @brief Updates the object’s state, typically for animation or physics.
     * @param dt The time difference between the current and previous frame.
     */
    virtual void update(const double dt);

    /**
     * @brief Renders the object using the provided view and projection matrices and sun lighting components.
     * @param viewMatrix The view matrix used for camera positioning.
     * @param projectionMatrix The projection matrix for perspective rendering.
     * @param components The lighting components of the sun (ambient, diffuse, specular, etc.).
     */
    virtual void render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, sunComponents components);

    /**
     * @brief Loads the model for the object from the file path.
     * @return `true` if the model was successfully loaded, `false` otherwise.
     */
    virtual bool loadModel();

    /**
     * @brief Loads a single mesh into the object’s geometry.
     * @param geometry Pointer to the geometry structure to store the mesh data.
     * @param mesh The Assimp mesh to load.
     * @param mat The material associated with the mesh.
     * @return `true` if the mesh was successfully loaded, `false` otherwise.
     */
    virtual bool loadSingleMesh(ObjectGeometry** geometry, aiMesh* mesh, aiMaterial* mat);

    /**
     * @brief Creates a texture from a file and optionally generates mipmaps.
     * @param fileName The file path to the texture image.
     * @param mipmap Whether to generate mipmaps for the texture.
     * @return The OpenGL texture ID.
     */
    static GLuint createTexture(const std::string& fileName, bool mipmap);

    /**
     * @brief Loads a 2D texture image into OpenGL.
     * @param fileName The file path to the image.
     * @param target The OpenGL texture target (e.g., GL_TEXTURE_2D).
     * @return `true` if the texture was successfully loaded, `false` otherwise.
     */
    static bool loadTexImage2D(const std::string& fileName, GLenum target);

    /**
     * @brief Converts a standard string to a wide string (for file paths).
     * @param str The string to convert.
     * @return The converted wide string.
     */
    static std::wstring stringToWString(const std::string& str);

protected:
    std::string MODEL_FILE_PATH; ///< Path to the 3D model file.

    Shader* shader;              ///< Pointer to the shader used for rendering.

    std::vector<ObjectGeometry*> geometry; ///< List of object geometry for the meshes.

    glm::vec3 size;              ///< The size of the object (scale).
    glm::vec3 position;          ///< The position of the object in 3D space.
    float angle;                 ///< Rotation angle for the object.
    glm::vec3 rotationAxis;      ///< The axis around which the object rotates.

    glm::mat4 modelMatrix;       ///< The model transformation matrix.
    glm::mat4 viewMatrix;        ///< The view transformation matrix (camera).
    glm::mat4 projectionMatrix;  ///< The projection transformation matrix (perspective).
};
