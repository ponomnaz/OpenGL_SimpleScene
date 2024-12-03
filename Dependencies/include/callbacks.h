#pragma once

#include "common_includes.h"
#include "Application.h"

void reshapeCb(GLFWwindow* window, int w, int h);

void keyboardCb(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouseMotionCb(GLFWwindow* window, double x, double y);

void mouseButtonCb(GLFWwindow* window, int button, int action, int mods);

void scrollCb(GLFWwindow* window, double xoffset, double yoffset);
