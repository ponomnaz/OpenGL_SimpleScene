#pragma once

#include "common_includes.h"
#include <IL/il.h>
#include "Camera.h"
#include "Shader.h"
#include "ObjectGeometry.h"

class Object {
public:

    Object(Shader* shader, const std::string path);
    virtual ~Object();

    virtual void update(const double dt);

    virtual void render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

    virtual bool loadModel();

    virtual bool loadSingleMesh(ObjectGeometry** geometry, aiMesh* mesh, aiMaterial* mat);

    static GLuint createTexture(const std::string& fileName, bool mipmap);

    static bool loadTexImage2D(const std::string& fileName, GLenum target);

    static std::wstring stringToWString(const std::string& str);

protected:
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