#pragma once

#include "common_includes.h"
#include "Sun.h"

/**
 * @class Shader
 * @brief Manages shader programs and their associated uniforms for rendering.
 *
 * The `Shader` class encapsulates the process of creating, setting up, and using
 * shaders for rendering 3D objects. It also manages the setting of various material
 * and lighting properties for the shaders.
 */
class Shader {
public:
    GLuint program; ///< OpenGL shader program ID.

    /**
     * @struct UniformLocations
     * @brief Stores the locations of various shader uniforms.
     *
     * This struct contains the locations for the vertex attributes (position, normal, etc.)
     * and material properties (diffuse, ambient, specular) as well as the sun and texture uniforms.
     */
    struct {
        GLint position;          ///< Location of the vertex position attribute.
        GLint normal;            ///< Location of the vertex normal attribute.

        GLint model;             ///< Location of the model matrix uniform.
        GLint view;              ///< Location of the view matrix uniform.

        GLint PVM;               ///< Location of the combined PVM matrix uniform.
        GLint normalMatrix;      ///< Location of the normal matrix uniform.

        GLint diffuse;           ///< Location of the diffuse material property uniform.
        GLint ambient;           ///< Location of the ambient material property uniform.
        GLint specular;          ///< Location of the specular material property uniform.
        GLint shininess;         ///< Location of the shininess material property uniform.

        GLint sunPosition;       ///< Location of the sun position uniform.
        GLint sunAmbient;        ///< Location of the sun ambient lighting uniform.
        GLint sunDiffuse;        ///< Location of the sun diffuse lighting uniform.
        GLint sunSpecular;       ///< Location of the sun specular lighting uniform.
        GLint globalAmbientLight;///< Location of the global ambient light uniform.

        GLint textureCoord;      ///< Location of the texture coordinate attribute.
        GLint texture;           ///< Location of the texture sampler uniform.
        GLint useTexture;        ///< Location of the texture usage flag uniform.
    } locations;

    /**
     * @brief Constructs a Shader object and initializes the program ID.
     */
    Shader();

    /**
     * @brief Destroys the Shader object and frees associated resources.
     */
    virtual ~Shader();

    /**
     * @brief Creates the shader program by loading and compiling vertex and fragment shaders.
     * @param vertexFile The path to the vertex shader file.
     * @param fragmentFile The path to the fragment shader file.
     */
    virtual void createProgram(const std::string vertexFile, const std::string fragmentFile);

    /**
     * @brief Sets up the shader program by retrieving uniform locations.
     * This function should be called after the shader program is created.
     */
    virtual void setUp(void);

    /**
     * @brief Activates the shader program for rendering.
     * @param use A flag indicating whether to activate (`true`) or deactivate (`false`) the shader program.
     */
    void useProgram(const bool use);

    /**
     * @brief Sets the model, view, and projection matrices for the shader program.
     * @param model The model matrix.
     * @param view The view matrix.
     * @param projection The projection matrix.
     */
    virtual void setMatrices(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

    /**
     * @brief Sets the material properties for the shader.
     * @param diffuse The diffuse color of the material.
     * @param ambient The ambient color of the material.
     * @param specular The specular color of the material.
     * @param shininess The shininess of the material.
     * @param texture The texture ID for the material (if any).
     */
    virtual void setMaterial(const glm::vec3& diffuse, const glm::vec3& ambient, const glm::vec3& specular, const float shininess, const GLuint texture);

    /**
     * @brief Sets the sun-related lighting components for the shader.
     * @param components A struct containing the sun's position, ambient, diffuse, specular lighting, and global ambient light.
     */
    virtual void setSun(const sunComponents& components);

private:
    /**
     * @brief Compiles and creates a shader from a given file path.
     * @param filePath The path to the shader file.
     * @param shaderType The type of shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
     * @return The compiled shader ID.
     */
    virtual unsigned int createShader(const std::string& filePath, const unsigned int shaderType);
};
