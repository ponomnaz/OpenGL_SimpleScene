#include "Application.h"

Application::Application() {
    width = 640;
    height = 480;

    execute = false;
    timeScale = 1.0f;
}

Application::~Application() {
    delete mainShader;
    delete skyBoxShader;
     
    delete camera;
    delete skyBox;
    delete sun;

    for (auto o : sceneObjects) {
        delete o;
    }
}

void Application::setUpGlfw() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return;
    }

    // Set OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    // Create the windowed mode window and OpenGL context
    window = glfwCreateWindow(width, height, WINDOW_NAME, NULL, NULL);
    if (!window) {
        std::cerr << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        return;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);


    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, &reshapeCb);
    glfwSetKeyCallback(window, &keyboardCb);
    glfwSetCursorPosCallback(window, &mouseMotionCb);
    glfwSetMouseButtonCallback(window, &mouseButtonCb);
    glfwSetScrollCallback(window, &scrollCb);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::setUpOpengl() {

    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Application::setUpShaders() {
    mainShader = new Shader();
    mainShader->createProgram("C:/OpenGL_SimpleScene/Scene/Shaders/default.vert", "C:/OpenGL_SimpleScene/Scene/Shaders/default.frag");
    mainShader->setUp();

    skyBoxShader = new SkyBoxShader();
    skyBoxShader->createProgram("C:/OpenGL_SimpleScene/Scene/Shaders/skyBox.vert", "C:/OpenGL_SimpleScene/Scene/Shaders/skyBox.frag");
    skyBoxShader->setUp();
}

void Application::setUpSceneObjects() {
    ilInit();

    camera = new Camera(mainShader, width, height);
    sun = new Sun();

    skyBox = new SkyBox(skyBoxShader, "C:/OpenGL_SimpleScene/Scene/Data/SkyBox/skybox");
    if (skyBox->loadModel())
        std::cerr << "NICE LOADING" << std::endl;

    Object* obj = new Object(mainShader, "C:/OpenGL_SimpleScene/Scene/Data/Duck/duck.obj");
    if (obj->loadModel())
        std::cerr << "NICE LOADING" << std::endl;
    sceneObjects.push_back(obj);
}

void Application::run() {
    execute = true;

    double lastTime = glfwGetTime();
    double accumulatedTime = 0;

    while (execute && !glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        accumulatedTime += currentTime - lastTime;
        lastTime = currentTime;

        if (accumulatedTime >= TIME_PER_FRAME) {
            timerCb(accumulatedTime * timeScale);
            displayCb();
            accumulatedTime -= TIME_PER_FRAME;
        }
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::timerCb(const double deltaTime) {
    sun->update(deltaTime);
    camera->update(deltaTime, keys);
    for (auto object : sceneObjects) {
        object->update(deltaTime);
    }
}

void Application::displayCb() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    camera->render();

    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 projectionMatrix = camera->getProjectionMatrix();
    sunComponents sunComponents = sun->getComponents();

    skyBox->render(viewMatrix, projectionMatrix, sunComponents.intensity);

    for (auto object : sceneObjects) {
        object->render(viewMatrix, projectionMatrix, sunComponents);
    }

    glDisable(GL_STENCIL_TEST);
    glfwSwapBuffers(window);
}

void Application::reshapeCbHandler(const int w, const int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
    camera->setWindowSize(w, h);
}

void Application::keyboardCbHandler(const int key, const int action, const int mods) {
    switch (action) {
    case GLFW_PRESS:
        keyPressed(key);
        break;
    case GLFW_REPEAT:
        keyRepeated(key);
        break;
    case GLFW_RELEASE:
        keyReleased(key);
        break;
    }
}

void Application::keyPressed(const int k) {
    switch (k)
    {
    case GLFW_KEY_ESCAPE:
        execute = false;
        break;
    case  GLFW_KEY_UP:
        changeScaleTimeFactor(1);
        break;
    case GLFW_KEY_DOWN:
        changeScaleTimeFactor(-1);
        break;
    default:
        keys.insert(k);
        break;
    }
}

void Application::keyReleased(const int k) {
    keys.erase(k);
}

void Application::keyRepeated(const int k) {
    switch (k)
    {
    case  GLFW_KEY_UP:
        changeScaleTimeFactor(1);
        break;
    case GLFW_KEY_DOWN:
        changeScaleTimeFactor(-1);
        break;
    }
}

void Application::mouseMotionCbHandler(const double x, const double y) {
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    glfwSetCursorPos(window, centerX, centerY);
    camera->setMousCord(x, y);
}

void Application::mouseButtonCbHandler(const int button, const int action) {
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        std::cerr << "x = " << camera->getPosition().x << " y = " << camera->getPosition().y << " z = " << camera->getPosition().z << std::endl;
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        std::cerr << "GLFW_MOUSE_BUTTON_RIGHT" << std::endl;
        break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        std::cerr << "GLFW_MOUSE_BUTTON_MIDDLE" << std::endl;
        break;
    }
}

void Application::scrollCbHandler(const double yoffset) {
    std::cerr << yoffset << std::endl;
}

void Application::changeScaleTimeFactor(const int val) {
    timeScale += val;

    if (timeScale < MIN_TIME_SCALE)
        timeScale = MIN_TIME_SCALE;
    else if (timeScale > MAX_TIME_SCALE)
        timeScale = MAX_TIME_SCALE;
}