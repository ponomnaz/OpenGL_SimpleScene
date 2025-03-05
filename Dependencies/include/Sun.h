#pragma once

#include "common_includes.h"

/**
 * @struct sunComponents
 * @brief Represents the properties of the sun's lighting in the scene.
 *
 * This struct holds information about the sun's position, ambient, diffuse,
 * and specular lighting components, along with global ambient light intensity.
 */
struct sunComponents {
    glm::vec3 position;           ///< The position of the sun in world space.
    glm::vec3 ambient;            ///< Ambient lighting component.
    glm::vec3 diffuse;            ///< Diffuse lighting component.
    glm::vec3 specular;           ///< Specular lighting component.
    glm::vec3 globalAmbientLight; ///< Overall ambient light affecting the scene.
    float intensity;              ///< Light intensity factor.
};

/**
 * @class Sun
 * @brief Simulates the movement and lighting effects of the sun in a scene.
 *
 * This class manages the sun's position, updates its movement over time,
 * and calculates lighting changes throughout the day.
 */
class Sun
{
public:
    /**
         * @brief Constructs the Sun object and initializes its properties.
         */
    Sun();

    /**
     * @brief Destroys the Sun object.
     */
    ~Sun();

    /**
     * @brief Updates the sun's position and lighting based on elapsed time.
     * @param dt Delta time (time elapsed since the last frame).
     */
    void update(const float dt);

    /**
     * @brief Retrieves the current time of day in the simulation.
     * @return A float representing the time of day.
     */
    float getDayTime() const;

    /**
     * @brief Retrieves the sun's lighting components.
     * @return A struct containing sun lighting parameters.
     */
    sunComponents getComponents() const;

    /**
     * @brief Resets the sun's day cycle to its initial state.
     */
    void reset();

private:
    const float RADIUS = 10.0f;     ///< Orbital radius of the sun.
    const float DAY_LENGTH = 240.0f; ///< Total duration of a day in the simulation.
    float dayTime;                   ///< Current time of day in the simulation.

    sunComponents components; ///< Stores the sun's lighting components.

    /**
     * @brief Computes the sun's position based on the time of day.
     */
    void calculatePosition();

    /**
     * @brief Computes the lighting effects based on the sun's position.
     */
    void calculateLighting();
};
