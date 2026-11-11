#include "window.hpp"

#include <stdexcept>


void Window::Init(unsigned short width, unsigned short height, const char *title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window!");
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
