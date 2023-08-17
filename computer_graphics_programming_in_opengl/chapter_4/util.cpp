#include "util.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "SOIL2/SOIL2.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string readShaderSource(const char* filePath)
{
    string content;
    ifstream fileStream(filePath, ios::in);
    string line;

    while (!fileStream.eof())
    {
        getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void printShaderLog(GLuint shader)
{
    int len = 0;
    int chWriten = 0;
    char* log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0)
    {
        log = (char*)malloc(len);
        if (log)
        {
            glGetShaderInfoLog(shader, len, &chWriten, log);
            cout << "Shader Info Log: " << log << endl;
            free(log);
        }
    }
}

void printProgramLog(int prog)
{
    int len = 0;
    int chWriten = 0;
    char* log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0)
    {
        log = (char*)malloc(len);
        if (log)
        {
            glGetProgramInfoLog(prog, len, &chWriten, log);
            cout << "Program Info Log: " << log << endl;
            free(log);
        }
    }
}

bool checkOpenGLError()
{
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        cout << "glError: " << glErr << endl;
        foundError = true;
        glErr = glGetError();
    }

    return foundError;
}

GLuint createShaderProgram()
{
    string vertShaderStr = readShaderSource("./vertShader.glsl");
    string fragShaderStr = readShaderSource("./fragShader.glsl");

    const char* vshaderSource = vertShaderStr.c_str();
    const char* fshaderSource = fragShaderStr.c_str();

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    GLint verCompiled;
    GLint fragCompiled;
    GLint linked;

    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &verCompiled);
    if (verCompiled != 1)
    {
        cout << "Vertex compilation failed" << endl;
        printShaderLog(vShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1)
    {
        cout << "Frag compilation failed" << endl;
        printShaderLog(fragCompiled);
    }

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    glLinkProgram(vfProgram);
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1)
    {
        cout << "link failed" << endl;
        printProgramLog(vfProgram);
    }

    return vfProgram;
}

GLuint loadTexture(const char* path)
{
    GLuint textureID;
    textureID = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureID == 0)
    {
        cout << "could not find texture: " << path << endl;
    }

    return textureID;
}

// 黄金材质：环境光、漫反射、镜面反射和光泽度
float* goldAmbient() {
    static float a[4] = { 0.2473f, 0.1995f, 0.0745f, 1 }; return
        (float*)a;
}
float* goldDiffuse() {
    static float a[4] = { 0.7516f, 0.6065f, 0.2265f, 1 }; return
        (float*)a;
}
float* goldSpecular() {
    static float a[4] = { 0.6283f, 0.5559f, 0.3661f, 1 }; return
        (float*)a;
}
float goldShininess() { return 51.2f; }
// 白银材质：环境光、漫反射、镜面反射和光泽度
float* silverAmbient() {
    static float a[4] = { 0.1923f, 0.1923f, 0.1923f, 1 }; return
        (float*)a;
}
float* silverDiffuse() {
    static float a[4] = { 0.5075f, 0.5075f, 0.5075f, 1 }; return
        (float*)a;
}
float* silverSpecular() {
    static float a[4] = { 0.5083f, 0.5083f, 0.5083f, 1 }; return
        (float*)a;
}
float silverShininess() { return 51.2f; }
// 青铜材质：环境光、漫反射、镜面反射和光泽度
float* bronzeAmbient() {
    static float a[4] = { 0.2125f, 0.1275f, 0.0540f, 1 }; return
        (float*)a;
}
float* bronzeDiffuse() {
    static float a[4] = { 0.7140f, 0.4284f, 0.1814f, 1 }; return
        (float*)a;
}
float* bronzeSpecular() {
    static float a[4] = { 0.3936f, 0.2719f, 0.1667f, 1 }; return
        (float*)a;
}
float bronzeShininess() { return 25.6f; }