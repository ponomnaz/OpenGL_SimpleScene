#pragma once

#include "common_includes.h"
#include "Application.h"

/**
 * @brief Callback function for window resizing.
 * @param window Pointer to the GLFW window.
 * @param w New width of the window.
 * @param h New height of the window.
 */
void reshapeCb(GLFWwindow* window, int w, int h);

/**
 * @brief Callback function for keyboard input.
 * @param window Pointer to the GLFW window.
 * @param key The key that was pressed or released.
 * @param scancode Platform-specific scancode of the key.
 * @param action Type of key action (press, release, repeat).
 * @param mods Modifier keys (Shift, Ctrl, Alt).
 */
void keyboardCb(GLFWwindow* window, int key, int scancode, int action, int mods);

/**
 * @brief Callback function for mouse movement.
 * @param window Pointer to the GLFW window.
 * @param x New x-coordinate of the mouse cursor.
 * @param y New y-coordinate of the mouse cursor.
 */
void mouseMotionCb(GLFWwindow* window, double x, double y);

/**
 * @brief Callback function for mouse button events.
 * @param window Pointer to the GLFW window.
 * @param button The mouse button that was pressed or released.
 * @param action Type of action (press or release).
 * @param mods Modifier keys (Shift, Ctrl, Alt).
 */
void mouseButtonCb(GLFWwindow* window, int button, int action, int mods);

/**
 * @brief Callback function for mouse scrolling.
 * @param window Pointer to the GLFW window.
 * @param xoffset Scroll offset along the x-axis.
 * @param yoffset Scroll offset along the y-axis.
 */
void scrollCb(GLFWwindow* window, double xoffset, double yoffset);
