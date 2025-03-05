#pragma once

#include "common_includes.h"
#include "Shader.h"

/**
 * @class Camera
 * @brief Represents a 3D camera that handles movement, rotation, and projection.
 */
class Camera {
public:
    /**
     * @brief Constructor for the Camera class.
     * @param shader Pointer to the shader used for rendering.
     * @param w Initial window width.
     * @param h Initial window height.
     */
    Camera(Shader* shader, const int w, const int h);

    /**
     * @brief Updates the camera position and orientation based on input.
     * @param dt Delta time for smooth movement.
     * @param keys Set of currently pressed keys.
     */
    void update(const float dt, std::unordered_set<int> keys);

    /**
     * @brief Renders the camera transformations to the shader.
     */
    void render();

    /**
     * @brief Sets the window size for aspect ratio adjustments.
     * @param w New window width.
     * @param h New window height.
     */
    void setWindowSize(const int w, const int h);

    /**
     * @brief Updates the stored mouse coordinates.
     * @param x New mouse x-coordinate.
     * @param y New mouse y-coordinate.
     */
    void setMousCord(const double x, const double y);

    /**
     * @brief Retrieves the view matrix (camera transformation).
     * @return The view matrix.
     */
    glm::mat4 getViewMatrix();

    /**
     * @brief Retrieves the projection matrix (perspective transformation).
     * @return The projection matrix.
     */
    glm::mat4 getProjectionMatrix();

    /**
     * @brief Retrieves the camera's current world position.
     * @return The camera position as a 3D vector.
     */
    glm::vec3 getPosition();

private:
    // Window dimensions
    int width;  ///< Window width.
    int height; ///< Window height.

    // Mouse input tracking
    double mousX; ///< Last known mouse X-coordinate.
    double mousY; ///< Last known mouse Y-coordinate.

    Shader* shader; ///< Pointer to the shader used for rendering.

    // Camera position and orientation
    glm::vec3 position; ///< Camera position in world space.
    float pitch;        ///< Up-and-down rotation (rotation around the x-axis).
    float yaw;          ///< Left-and-right rotation (rotation around the y-axis).

    glm::vec3 right;    ///< Local right direction of the camera.
    glm::vec3 up;       ///< Local up direction of the camera.
    glm::vec3 forwards; ///< Local forward direction of the camera.

    // Projection parameters
    float fov;       ///< Field of view (zoom level).
    float nearPlane; ///< Near clipping plane.
    float farPlane;  ///< Far clipping plane.

    // Movement and rotation settings
    float speed;       ///< Camera movement speed.
    float sensitivity; ///< Mouse sensitivity for rotation.

    /**
     * @enum Jump
     * @brief Represents different states of vertical movement (jumping).
     */
    enum Jump {
        Jumped,      ///< The jump action has been performed.
        IsJumping,   ///< The camera is currently in the air.
        IsLanding,   ///< The camera is descending.
        Landed       ///< The camera has landed on the ground.
    };

    Jump verticalMovment; ///< Current jump state.
    float jumpSpeed;      ///< Speed at which the camera jumps.
    float gravity;        ///< Gravity applied to the camera.
    float verticalSpeed;  ///< Current vertical movement speed.

    const glm::vec3 global_up = { 0.0f, 1.0f, 0.0f }; ///< Global up direction.

    /**
     * @brief Moves the camera based on user input.
     * @param keys Set of currently pressed keys.
     */
    void move(std::unordered_set<int> keys);

    /**
     * @brief Rotates the camera based on mouse movement.
     */
    void rotate();

    /**
     * @brief Computes the camera's local axes based on its orientation.
     */
    void computeLocalAxes();
};