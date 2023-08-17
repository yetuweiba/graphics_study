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

// �ƽ���ʣ������⡢�����䡢���淴��͹����
float* goldAmbient();
float* goldDiffuse();
float* goldSpecular();
float goldShininess();
// �������ʣ������⡢�����䡢���淴��͹����
float* silverAmbient();
float* silverDiffuse();
float* silverSpecular();
float silverShininess();
// ��ͭ���ʣ������⡢�����䡢���淴��͹����
float* bronzeAmbient();
float* bronzeDiffuse();
float* bronzeSpecular();
float bronzeShininess();