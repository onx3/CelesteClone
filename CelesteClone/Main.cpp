#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include <iostream>

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(800, 600, "Game Window", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("Assets/Shaders/quad.vert", "Assets/Shaders/quad.frag");
    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.7f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        renderer.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}