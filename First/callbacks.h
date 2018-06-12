#pragma once

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

extern double zoom;
extern double center[2];

void mouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods);
