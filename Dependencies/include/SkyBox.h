#pragma once

#include "common_includes.h"
#include "SkyBoxShader.h"
#include "Object.h"

/**
 * @class SkyBox
 * @brief Manages the skybox rendering, including loading and drawing the skybox model.
 *
 * This class interacts with the `SkyBoxShader` and an `ObjectGeometry` to render a skybox
 * based on a given model file and shader, adjusting the rendering based on view and projection matrices.
 */
class SkyBox {
public:
    /**
     * @brief Constructs the SkyBox object with the given shader and model file.
     * @param shader Pointer to the `SkyBoxShader` used for rendering the skybox.
     * @param file Path to the model file used for the skybox.
     */
    SkyBox(SkyBoxShader* shader, std::string file);

    /**
     * @brief Destroys the SkyBox and frees associated resources.
     */
    ~SkyBox();

    /**
     * @brief Loads the model for the skybox from the given file path.
     * @return `true` if the model is successfully loaded, `false` otherwise.
     */
    bool loadModel();

    /**
     * @brief Renders the skybox with the given view and projection matrices.
     * @param viewMatrix The view matrix to position the camera.
     * @param projectionMatrix The projection matrix for perspective rendering.
     * @param sunIntensity The intensity of the sun's lighting affecting the skybox.
     */
    void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const float sunIntensity);

private:
    std::string MODEL_FILE_PATH; ///< Path to the skybox model file.

    SkyBoxShader* shader;        ///< Pointer to the shader used for rendering the skybox.

    ObjectGeometry* geometry;    ///< Pointer to the geometry object for the skybox.
};
