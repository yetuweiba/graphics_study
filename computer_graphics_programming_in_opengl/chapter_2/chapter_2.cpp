#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

#define numVAOs 1

GLuint  renderingProgram;
GLuint  vao[numVAOs];

GLuint createShaderProgram()
{
    const char* vshaderSource =
        "#version 330 core\n"
        "void main(void) \n"
        "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0);}";

    const char* fshaderSource =
        "#version 330 core\n"
        "out vec4 color; \n"
        "void main(void) \n"
        "{color = vec4(0.0, 0.0, 1.0, 1.0);}";

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}

using namespace std;

void init(GLFWwindow* window)
{
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currTime)
{
    glUseProgram(renderingProgram);
    glPointSize(30.f);
    glDrawArrays(GL_POINTS, 0, 1);
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
