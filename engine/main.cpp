#include <iostream>
#include <GLFW/glfw3.h>

int main(void) {
    GLFWwindow* window;

    glfwInit();

    window = glfwCreateWindow(640,480, "Hello World", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}