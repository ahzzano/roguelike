// #define SDL_MAIN_HANDLED

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

#define ASSETS_PATH "./assets";

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

int main(int argc, char *argv[]) {
  std::cout << ASSETS_PATH;

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);

  glfwMakeContextCurrent(window);

  int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  if (version == 0) {
    std::cout << "Failed to initialize OpenGL Context\n";
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);

  int width, height;
  while (!glfwWindowShouldClose(window)) {

    glfwGetFramebufferSize(window, &width, &height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
