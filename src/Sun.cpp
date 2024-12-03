#include "Sun.h"

Sun::Sun() {
	dayTime = 100.0f;
}

Sun::~Sun() {

}

void Sun::update(const float dt) {
    dayTime = fmod(dayTime + dt, DAY_LENGTH);
    calculatePosition();
    calculateLighting();
 }

float Sun::getDayTime() const {
    return dayTime;
}

sunComponents Sun::getComponents() const {
    return components;
}

void Sun::calculatePosition() {
    float angle = (dayTime / DAY_LENGTH) * 2.0f * glm::pi<float>();
    float x = RADIUS * cos(angle - glm::pi<float>() / 2.0f);
    float y = RADIUS * sin(angle - glm::pi<float>() / 2.0f);
    if (y >= 0)
        components.position = glm::vec3(x, y, 0.0f);
    else
        components.position = glm::vec3(0.0f, 10.0f, 0.0f);
    
}

void Sun::calculateLighting() {
    float normalizedTime = dayTime / DAY_LENGTH;
    components.intensity = glm::max(0.1f, glm::cos(normalizedTime * glm::pi<float>() * 2.0f - glm::pi<float>()));

    if (components.intensity == 0.1f) {
        components.ambient = glm::vec3(0.05f, 0.05f, 0.1f);
        components.diffuse = glm::vec3(0.2f, 0.2f, 0.4f);
        components.specular = glm::vec3(0.3f, 0.3f, 0.5f);
    } else {
        components.ambient = glm::vec3(0.1f, 0.1f, 0.1f) * components.intensity;
        components.diffuse = glm::vec3(1.0f, 1.0f, 0.8f) * components.intensity;
        components.specular = glm::vec3(1.0f, 0.8f, 0.8f) * components.intensity;
    }

    components.globalAmbientLight = glm::vec3(0.1f, 0.1f, 0.1f);
}

void Sun::reset() {
    dayTime = 0.0f;
}