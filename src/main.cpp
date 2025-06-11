#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>

#include "renderer/shader.hpp"
#include "utils/fileio.hpp"
#include "renderer/renderer.hpp"
#include "renderer/buffers.hpp"
#include "renderer/texture.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark(); // or ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

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
        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui UI
        ImGui::Begin("Control Panel"); // side pane
        ImGui::Text("Parameters:");

        static float myFloat = 0.03f;
        ImGui::SliderFloat("Height Scale", &myFloat, 0.0f, 0.1f);
        static float timeSpeed = 1.0f;
        ImGui::SliderFloat("Time Scale", &timeSpeed, 0.1f, 2.0f);

        ImGui::End();
        // Your simulation logic
        process_input(window, mouseX, mouseY, time);
        time += 0.05f;

        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

        shaderProgram.setFloat("time", time);
        shaderProgram.setFloat("timeSpeed", timeSpeed);
        shaderProgram.setFloat("heightScale", myFloat);

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

        // Render scene
        Renderer.clear();
        Renderer.draw(va, ib, shaderProgram);
        shaderProgram.autoreload();

        // Render ImGui
        ImGui::Render();                                        // <--- REQUIRED
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // <--- REQUIRED

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
