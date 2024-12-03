#pragma once

#include "common_includes.h"
#include "callbacks.h"

#include "Camera.h"
#include "Object.h"
#include "Shader.h"
#include "SkyBox.h"
#include "Sun.h"

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
    void scrollCbHandler(const double yoffset);

private:
    const char* WINDOW_NAME = "Scene";

    const float FRAME_RATE = 60.0f;

    const float TIME_PER_FRAME = 1.0f / FRAME_RATE;

    const int MIN_TIME_SCALE = 1;
    const int MAX_TIME_SCALE = 50;

    int timeScale;

    bool execute;

    GLFWwindow* window;

    int width;
    int height;

    std::unordered_set<int> keys;

    Camera* camera;

    Shader* mainShader;

    SkyBoxShader* skyBoxShader;
    SkyBox* skyBox;

    Sun* sun;

    std::vector<Object*> sceneObjects;

    void timerCb(const double deltaTime);
    void displayCb();

    void keyPressed(const int k);
    void keyReleased(const int k);
    void keyRepeated(const int k);

    void changeScaleTimeFactor(const int val);
};