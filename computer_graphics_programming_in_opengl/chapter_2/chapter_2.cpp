#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>
#include <fstream>

#define numVAOs 1
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

GLuint  renderingProgram;
GLuint  vao[numVAOs];

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
    //const char* vshaderSource =
    //    "#version 330 core\n"
    //    "void main(void) \n"
    //    "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0);}";

    //const char* fshaderSource =
    //    "#version 330 core\n"
    //    "out vec4 color; \n"
    //    "void main(void) \n"
    //    "{color = vec4(0.0, 0.0, 1.0, 1.0);}";
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

void init(GLFWwindow* window)
{
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

float x = 0.0f;
float inc = 0.01f;

void display(GLFWwindow* window, double currTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    x += inc;
    if (x > 1.0f)
    {
        inc = -0.01f;
    }
    if (x < -1.0f)
    {
        inc = 0.01f;
    }

    GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
    glProgramUniform1f(renderingProgram, offsetLoc, x);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{
    if (!glfwInit())
    {
        cout << "glfwinit failed" << endl;
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(800, 600, "chapter2", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        cout << "glew init failed" << endl;
        return 0;
    }

    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window))
    {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
}
