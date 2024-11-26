#include "Application.h"

Application::Application() {
    width = 640;
    height = 480;
}

Application::~Application() {
    delete mainShader;
    delete camera;

    for (auto o : sceneObjects) {
        delete o;
    }

    glfwTerminate();
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::setUpOpengl() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Application::setUpShaders() {
    mainShader = new Shader();
    mainShader->createProgram("C:/OpenGL_SimpleScene/Scene/src/default.vert", "C:/OpenGL_SimpleScene/Scene/src/default.frag");
    mainShader->setUp();
}

void Application::setUpSceneObjects() {
    camera = new Camera(mainShader, width, height);

    Object* obj = new Object(mainShader, "C:/OpenGL_SimpleScene/Scene/Data/Duck/duck.obj");
    if (obj->loadModel())
        std::cerr << "NICE LOADING" << std::endl;
    sceneObjects.push_back(obj);
}

void Application::run() {
    double lastTime = glfwGetTime();
    double accumulatedTime = 0;

    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        accumulatedTime += currentTime - lastTime;
        lastTime = currentTime;

        if (accumulatedTime >= TIME_PER_FRAME) {
            timerCb(accumulatedTime);
            displayCb();
            accumulatedTime -= TIME_PER_FRAME;
        }

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::timerCb(const double deltaTime) {
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
    for (auto object : sceneObjects) {
        object->render(viewMatrix, projectionMatrix);
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
        
        break;
    case GLFW_RELEASE:
        keyReleased(key);
        break;
    default:
        break;
    }
}

void Application::keyPressed(const int k) {
    switch (k)
    {
    case GLFW_KEY_ESCAPE:

        break;
    default:
        keys.insert(k);
        break;
    }
}

void Application::keyReleased(const int k) {
    keys.erase(k);
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
        std::cerr << "GLFW_MOUSE_BUTTON_LEFT" << std::endl;
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        std::cerr << "GLFW_MOUSE_BUTTON_RIGHT" << std::endl;
        break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        std::cerr << "GLFW_MOUSE_BUTTON_MIDDLE" << std::endl;
        break;
    default:
        break;
    }
}