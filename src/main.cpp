#include "Application.h"

int main(void)
{
    Application* app = new Application();
    app->setUpGlfw();
    app->setUpOpengl();
    app->setUpShaders();
    app->setUpSceneObjects();

    app->run();

    delete app;
    return 0;
}