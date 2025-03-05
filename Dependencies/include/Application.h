#pragma once

#include "common_includes.h"
#include "callbacks.h"

#include "Camera.h"
#include "Object.h"
#include "Shader.h"
#include "SkyBox.h"
#include "Sun.h"

/**
 * @class Application
 * @brief Manages the entire application lifecycle, including setup, rendering, and event handling.
 */
class Application {
public:
    /**
    * @brief Constructor that initializes the application.
    */
    Application();

    /**
    * @brief Destructor that cleans up resources.
    */
    ~Application();

    /**
     * @brief Sets up GLFW (window creation, OpenGL context, input handling).
     */
    void setUpGlfw();

    /**
     * @brief Sets up OpenGL (rendering settings, depth testing, blending).
     */
    void setUpOpengl();

    /**
     * @brief Loads and initializes shaders used in the application.
     */
    void setUpShaders();

    /**
     * @brief Creates and configures scene objects.
     */
    void setUpSceneObjects();

    /**
     * @brief Runs the main application loop.
     */
    void run();

    // Callback Handlers for window events

    /**
     * @brief Handles window resizing events.
     * @param w New window width.
     * @param h New window height.
     */
    void reshapeCbHandler(const int w, const int h);

    /**
     * @brief Handles keyboard input events.
     * @param key The key pressed/released.
     * @param action The action (press, release, repeat).
     * @param mods Modifier keys (shift, ctrl, alt).
     */
    void keyboardCbHandler(const int key, const int action, const int mods);
    
    /**
     * @brief Handles mouse movement events.
     * @param x New mouse X position.
     * @param y New mouse Y position.
     */
    void mouseMotionCbHandler(const double x, const double y);
    
    /**
     * @brief Handles mouse button events.
     * @param button The mouse button pressed/released.
     * @param action The action (press/release).
     */
    void mouseButtonCbHandler(const int button, const int action);
    
    /**
     * @brief Handles mouse scroll events.
     * @param yoffset Scroll offset (positive/negative).
     */
    void scrollCbHandler(const double yoffset);

private:
    // Window properties
    const char* WINDOW_NAME = "Scene"; ///< Window title.

    // Frame rate control
    const float FRAME_RATE = 60.0f; ///< Target frame rate.
    const float TIME_PER_FRAME = 1.0f / FRAME_RATE; ///< Time per frame in seconds.

    // Time scaling limits
    const int MIN_TIME_SCALE = 1; ///< Minimum time scale factor.
    const int MAX_TIME_SCALE = 50; ///< Maximum time scale factor.

    int timeScale; ///< Current time scale factor.

    bool execute; ///< Flag to control the main loop execution.

    GLFWwindow* window; ///< Pointer to the GLFW window.

    int width;  ///< Current window width.
    int height; ///< Current window height.

    std::unordered_set<int> keys; ///< Set of currently pressed keys.

    Camera* camera; ///< Camera for scene navigation.

    Shader* mainShader; ///< Main shader for rendering objects.

    SkyBoxShader* skyBoxShader; ///< Shader for rendering the skybox.
    SkyBox* skyBox; ///< Skybox object.

    Sun* sun; ///< Sun object representing the light source.

    std::vector<Object*> sceneObjects; ///< List of all objects in the scene.

    /**
     * @brief Timer callback for updating logic based on elapsed time.
     * @param deltaTime Time since last frame.
     */
    void timerCb(const double deltaTime);

    /**
     * @brief Callback for rendering the scene.
     */
    void displayCb();

    // Keyboard input handling

    /**
     * @brief Called when a key is pressed.
     * @param k The key code.
     */
    void keyPressed(const int k);

    /**
     * @brief Called when a key is released.
     * @param k The key code.
     */
    void keyReleased(const int k);

    /**
     * @brief Called when a key is held down (repeat event).
     * @param k The key code.
     */
    void keyRepeated(const int k);

    /**
     * @brief Adjusts the time scale factor.
     * @param val Amount to change the time scale by.
     */
    void changeScaleTimeFactor(const int val);
};