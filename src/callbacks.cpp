#include "callbacks.h"

void reshapeCb(GLFWwindow* window, int w, int h) {
    auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app)
        app->reshapeCbHandler(w, h);
};

void keyboardCb(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app)
        app->keyboardCbHandler(key, action, mods);
}

void mouseMotionCb(GLFWwindow* window, double x, double y) {
    auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app)
        app->mouseMotionCbHandler(x, y);
}

void mouseButtonCb(GLFWwindow* window, int button, int action, int mods) {
    auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app)
        app->mouseButtonCbHandler(button, action);
}

void scrollCb(GLFWwindow* window, double xoffset, double yoffset) {
    auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app)
        app->scrollCbHandler(yoffset);
}