#include "Camera.h"


Camera::Camera(Shader* shader, const int w, const int h) {
    this->shader = shader;
    setWindowSize(w, h);

    position = { 0.0f, 0.0f, 1.0f };
    eulers = { 0.0f, 0.0f, 0.0f };

    speed = 0.05f;
    sensitivity = 0.2f;

    fov = 45.0f;
    nearPlane = 0.1f;
    farPlane = 10.0f;

    computeLocalAxes();
}

void Camera::update(const float dt, std::unordered_set<int> keys) {
    move(keys);
    rotate();
    computeLocalAxes();
}

void Camera::render() {
    shader->useProgram();
    glm::mat4 view = getViewMatrix();
    glm::mat4 projection = getProjectionMatrix();

    glUniformMatrix4fv(shader->locations.projection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(shader->locations.view, 1, GL_FALSE, glm::value_ptr(view));
    shader->notUseProgram();
}

void Camera::setWindowSize(int w, int h) {
    width = w;
    height = h;
    setMousCord(w / 2, h / 2);
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + forwards, up);
}
glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(glm::radians(fov), (float)width / height, nearPlane, farPlane);
}

void Camera::computeLocalAxes() {
    float theta = glm::radians(eulers.z);
    float phi = glm::radians(eulers.y);

    forwards = {
        glm::cos(theta) * glm::cos(phi),
        glm::sin(theta) * glm::cos(phi),
        glm::sin(phi)
    };
    right = glm::normalize(glm::cross(forwards, global_up));
    up = glm::normalize(glm::cross(right, forwards));
}

void Camera::move(std::unordered_set<int> keys) {
    glm::vec3 dPos = { 0.0f, 0.0f, 0.0f };
    if (keys.count(GLFW_KEY_W))
        dPos.x += 1.0f;
    if (keys.count(GLFW_KEY_A))
        dPos.y -= 1.0f;
    if (keys.count(GLFW_KEY_S))
        dPos.x -= 1.0f;
    if (keys.count(GLFW_KEY_D))
        dPos.y += 1.0f;

    if (glm::length(dPos) > 0.1f) {
        dPos = glm::normalize(dPos);
        position += speed * (dPos.x * forwards + dPos.y * right);
    }
}

void Camera::rotate() {
    glm::vec3 dEulers = { 0.0f, 0.0f, 0.0f };

    float centerX = width / 2.0f;
    float centerY = height / 2.0f;

    dEulers.z = -sensitivity * static_cast<float>(mousX - centerX);
    dEulers.y = -sensitivity * static_cast<float>(mousY - centerY);

    setMousCord(centerX, centerY);

    eulers.y = fminf(89.0f, fmaxf(-89.0f, eulers.y + dEulers.y));

    eulers.z += dEulers.z;
    if (eulers.z > 360)
        eulers.z -= 360;
    else if (eulers.z < 0)
        eulers.z += 360;
}

void Camera::setMousCord(const double x, const double y) {
    mousX = x;
    mousY = y;
}