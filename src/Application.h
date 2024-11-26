#pragma once

#include "common_includes.h"
#include "callbacks.h"

#include "Camera.h"
#include "Object.h"
#include "Shader.h"

class Application {
public:
    Application();
    ~Application();

    void setUpGlfw();
    void setUpOpengl();
    void setUpShaders();
    void setUpSceneObjects();

    void run();

    void reshapeCbHandler(const int w, const int h);
    void keyboardCbHandler(const int key, const int action, const int mods);
    void mouseMotionCbHandler(const double x, const double y);
    void mouseButtonCbHandler(const int button, const int action);

private:
    const char* WINDOW_NAME = "Scene";

    const float FRAME_RATE = 60.0f;

    const float TIME_PER_FRAME = 1.0f / FRAME_RATE;

    GLFWwindow* window;

    int width;
    int height;

    std::unordered_set<int> keys;

    Camera* camera;

    Shader* mainShader;

    std::vector<Object*> sceneObjects;

    void timerCb(const double deltaTime);
    void displayCb();

    void keyPressed(const int k);
    void keyReleased(const int k);
};