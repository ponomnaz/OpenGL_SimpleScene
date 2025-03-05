#pragma once
#include "Shader.h"

/**
 * @class SkyBoxShader
 * @brief Specialized shader for rendering a skybox.
 *
 * This class extends the `Shader` class to manage uniforms specific to skybox rendering,
 * such as inverse projection-view matrix and sun intensity.
 */
class SkyBoxShader : public Shader {
public:
    /**
     * @struct UniformLocations
     * @brief Stores the locations of shader uniforms.
     *
     * This struct holds the uniform locations for vertex coordinates,
     * inverse projection-view matrix, skybox texture sampler, and sun intensity.
     */
    struct {
        GLint coord;        ///< Location of the vertex coordinate attribute.
        GLint inversePV;    ///< Location of the inverse projection-view matrix uniform.
        GLint sampler;      ///< Location of the skybox texture sampler uniform.
        GLint sunIntensity; ///< Location of the sun intensity uniform.
    } locations;

    /**
     * @brief Constructs the SkyBoxShader and initializes shader programs.
     */
    SkyBoxShader();

    /**
     * @brief Sets up the shader by retrieving uniform locations.
     * This function overrides the base `Shader` setup.
     */
    void setUp(void) override;

    /**
     * @brief Sets the shader uniforms for skybox rendering.
     * @param inversePV The inverse of the projection-view matrix.
     * @param intensity The intensity of the sunlight affecting the skybox.
     */
    void setUniforms(const glm::mat4 inversePV, const float intensity);
};
