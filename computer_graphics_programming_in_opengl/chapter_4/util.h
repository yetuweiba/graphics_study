#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>

std::string readShaderSource(const char* filePath);

void printShaderLog(GLuint shader);

void printProgramLog(int prog);

bool checkOpenGLError();

GLuint createShaderProgram();

GLuint loadTexture(const char* path);