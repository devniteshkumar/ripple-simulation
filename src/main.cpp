#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>

#include "renderer/shader.hpp"
#include "utils/fileio.hpp"
#include "renderer/renderer.hpp"
#include "renderer/buffers.hpp"
#include "renderer/texture.hpp"

// Callback to adjust viewport on window resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window, int &mouseX, int &mouseY, float &time)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        mouseX = static_cast<int>(x);
        mouseY = static_cast<int>(y);
        time = 0.0f;
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int screenWidth = mode->width;
    int screenHeight = mode->height;

    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Triangle", NULL, NULL);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
        -0.5f, 0.5f, 0.0f, 1.0f, // Top-left
        0.5f, 0.5f, 1.0f, 1.0f,  // Top-right
        0.5f, -0.5f, 1.0f, 0.0f, // Bottom-right
        -0.5f, -0.5f, 0.0f, 0.0f // Bottom-left
    };

    unsigned int indices[] = {
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
    };

    Shader shaderProgram(
        fileio_getpath("src/shader/ripple.vert"),
        fileio_getpath("src/shader/ripple.frag"));

    vertexArray va;
    vertexBuffer vb(vertices, sizeof(vertices));
    vertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va.bind();
    va.AddBuffer(vb, layout);
    indexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

    texture Texture(fileio_getpath("assets/water_texture.jpg"));
    Texture.bind();
    shaderProgram.setInt("uTexture", 0);

    renderer Renderer;
    Renderer.draw(va, ib, shaderProgram);

    int mouseX = -1, mouseY = -1;
    float time = 1000.0f;

    while (!glfwWindowShouldClose(window))
    {
        process_input(window, mouseX, mouseY, time);
        time += 0.05f;

        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

        shaderProgram.setFloat("time", time);
        shaderProgram.setFloat("heightScale", 0.03f);

        if (mouseX >= 0 && mouseY >= 0)
        {
            shaderProgram.setVec2("rippleCenter", glm::vec2(
                                                      static_cast<float>(mouseX) / fbWidth,
                                                      1.0f - static_cast<float>(mouseY) / fbHeight));
        }
        else
        {
            shaderProgram.setVec2("rippleCenter", glm::vec2(-1.0f, -1.0f));
        }

        Renderer.clear();
        Renderer.draw(va, ib, shaderProgram);
        shaderProgram.autoreload();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
