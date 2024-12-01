#pragma once

#include "common_includes.h"
#include "Shader.h"

class Camera {
public:

    Camera(Shader* shader, const int w, const int h);

    void update(const float dt, std::unordered_set<int> keys);

    void render();

    void setWindowSize(const int w, const int h);
    void setMousCord(const double x, const double y);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::vec3 getPosition();

private:
    int width;
    int height;

    double mousX;
    double mousY;

    Shader* shader;

    glm::vec3 position;
    float pitch;            // up-and-down, rotation around the x-axis
    float yaw;              // left-and-righ, rotation around the y-axis

    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 forwards;

    float fov;
    float nearPlane;
    float farPlane;

    float speed;
    float sensitivity;

    const glm::vec3 global_up = { 0.0f, 1.0f, 0.0f };

    void move(std::unordered_set<int> keys);
    void rotate();
    void computeLocalAxes();
};