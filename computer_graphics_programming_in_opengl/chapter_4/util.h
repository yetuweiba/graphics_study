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

// 黄金材质：环境光、漫反射、镜面反射和光泽度
float* goldAmbient();
float* goldDiffuse();
float* goldSpecular();
float goldShininess();
// 白银材质：环境光、漫反射、镜面反射和光泽度
float* silverAmbient();
float* silverDiffuse();
float* silverSpecular();
float silverShininess();
// 青铜材质：环境光、漫反射、镜面反射和光泽度
float* bronzeAmbient();
float* bronzeDiffuse();
float* bronzeSpecular();
float bronzeShininess();