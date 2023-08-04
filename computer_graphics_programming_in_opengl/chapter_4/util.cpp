#include "util.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
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