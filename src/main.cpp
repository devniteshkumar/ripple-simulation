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

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Triangle", NULL, NULL);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
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
    va.AddBuffer(vb, layout); // Set layout
    indexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

    texture Texture(fileio_getpath("assets/water_texture.jpg"));
    Texture.bind();
    shaderProgram.setUniform1i("uTexture", 0);

    renderer Renderer;
    Renderer.draw(va, ib, shaderProgram);
    // int location = glGetUniformLocation(shaderProgram.ID, "uColor");
    // assert(location != -1);

    // float r = 0.0f;
    // float increment = 0.05f;
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        Renderer.clear();
        // shaderProgram.setUniform4("uColor", r, 0.3f, 0.8f, 1.0f);
        // r += increment;
        // if (r > 1.0f || r < 0.0f)
        //     increment *= -1;

        Renderer.draw(va, ib, shaderProgram);
        shaderProgram.autoreload();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
