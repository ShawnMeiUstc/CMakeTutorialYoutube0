#include <iostream>
#include "HelloCmakeConfig.h"

#ifdef USE_ADDER
#include <adder.h>
#endif

#ifdef USE_GLFW
#include <GLFW/glfw3.h>
#endif

int main(int argc, char **argv)
{
    std::cout << "Hello Cmake!" << std::endl;
#ifdef USE_ADDER
    std::cout << "Use adder library" << add(1.0, 3.5) << std::endl;
#endif
    std::cout << "The " << argv[0] << " Version" << HelloCmake_VERSION_MAJOR << "." << HelloCmake_VERSION_MINOR << std::endl;
#ifdef USE_GLFW

    GLFWwindow *window;
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(300, 300, "ForFun", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    while (!glfwWindowShouldClose(window))
    {
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
#endif
}