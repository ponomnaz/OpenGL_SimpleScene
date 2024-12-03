#pragma once

#include "common_includes.h"

struct sunComponents {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 globalAmbientLight;
    float intensity;
};

class Sun
{
public:
    Sun();
    ~Sun();

    void update(const float dt);

    float getDayTime() const;

    sunComponents getComponents() const;

    void reset();

private:

    const float RADIUS = 10.0f;
    const float DAY_LENGTH = 240.0f;
    float dayTime;

    sunComponents components;

    void calculatePosition();

    void calculateLighting();

};
