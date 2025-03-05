#include "Camera.h"


Camera::Camera(Shader* shader, const int w, const int h) {
    this->shader = shader;
    setWindowSize(w, h);

    position = { 0.0f, 1.0f, 0.0f };
    pitch = 0.0f;
    yaw = 0.0f;

    speed = 0.05f;
    sensitivity = 0.2f;

    fov = 45.0f;
    nearPlane = 0.1f;
    farPlane = 10.0f;

    verticalMovment = Landed;
    jumpSpeed = 0.2f;
    gravity = 0.01f;
    computeLocalAxes();
}

void Camera::update(const float dt, std::unordered_set<int> keys) {
    move(keys);
    rotate();
    computeLocalAxes();
}

void Camera::render() {
    shader->useProgram(true);
    glm::mat4 view = getViewMatrix();
    glm::mat4 projection = getProjectionMatrix();

    glUniformMatrix4fv(shader->locations.view, 1, GL_FALSE, glm::value_ptr(view));
    shader->useProgram(false);
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

glm::vec3 Camera::getPosition() {
    return position;
}

void Camera::computeLocalAxes() {
    float phi = glm::radians(pitch);
    float theta = glm::radians(yaw);

    forwards = {
        glm::cos(phi) * glm::cos(theta),
        glm::sin(phi),
        glm::cos(phi) * glm::sin(theta)
    };

    right = glm::normalize(glm::cross(forwards, global_up));
    up = glm::normalize(glm::cross(right, forwards));
}

void Camera::move(std::unordered_set<int> keys) {
    glm::vec3 dPos = { 0.0f, 0.0f, 0.0f };
    if (keys.count(GLFW_KEY_W))
        dPos.z += 1.0f;
    if (keys.count(GLFW_KEY_A))
        dPos.x -= 1.0f;
    if (keys.count(GLFW_KEY_S))
        dPos.z -= 1.0f;
    if (keys.count(GLFW_KEY_D))
        dPos.x += 1.0f;

    if (glm::length(dPos) > 0.1f) {
        dPos = glm::normalize(dPos);
        float y = position.y;
        position += speed * (dPos.z * forwards + dPos.x * right);
        position.y = y;
    }

    switch (verticalMovment)
    {
    case Camera::Jumped:
        verticalSpeed = jumpSpeed;
        verticalMovment = IsJumping;
        break;
    case Camera::IsJumping:
        position.y += verticalSpeed;
        verticalSpeed -= gravity;
        if (verticalSpeed <= 0.0f) {
            verticalMovment = IsLanding;
        }
        break;
    case Camera::IsLanding:
        position.y += verticalSpeed;
        verticalSpeed -= gravity;
        if (position.y <= 1.0f) {
            position.y = 1.0f;
            verticalMovment = Landed;
        }
        break;
    case Camera::Landed:
        if (keys.count(GLFW_KEY_SPACE)) {
            verticalMovment = Jumped;
        }
        break;
    }
}

void Camera::rotate() {
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;

    float dPitch = sensitivity * static_cast<float>(mousY - centerY);
    float dYaw = sensitivity * static_cast<float>(mousX - centerX);

    setMousCord(centerX, centerY);

    pitch = fminf(89.0f, fmaxf(-89.0f, pitch - dPitch));

    yaw += dYaw;
    if (yaw > 360)
        yaw -= 360;
    else if (yaw < 0)
        yaw += 360;
}

void Camera::setMousCord(const double x, const double y) {
    mousX = x;
    mousY = y;
}