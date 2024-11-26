#pragma once

#include "common_includes.h"
#include "Camera.h"
#include "Shader.h"
#include "ObjectGeometry.h"

class Object {
public:

    Object(Shader* shader, const std::string path);
    ~Object();

    void update(const double dt);

    void render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

    bool loadModel();

    bool loadSingleMesh(ObjectGeometry** geometry, aiMesh* mesh, aiMaterial* mat);

private:
    std::string MODEL_FILE_PATH;

    Shader* shader;

    std::vector<ObjectGeometry*> geometry;

    glm::vec3 size;
    glm::vec3 position;
    float angle;
    glm::vec3 rotationAxis;

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};