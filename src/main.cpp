// #define SDL_MAIN_HANDLED

#include <GLFW/glfw3.h>
#include <iostream>

#define ASSETS_PATH "./assets";

int main(int argc, char *argv[]) {
  std::cout << ASSETS_PATH;

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);

  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
