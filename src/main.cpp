/**
 *   Hello! Welcome to my Roguelike game
 */

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include "renderer.hpp"

#define ASSETS_PATH "./assets";

Rect player_rect;
bool wPressedDown = false;
bool sPressedDown = false;

bool isWireframe = false;

const float sqrtOf2 = 1.41421356237;

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    wPressedDown = true;
  }
  if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    sPressedDown = true;
  }

  if (key == GLFW_KEY_T && action == GLFW_PRESS) {
    isWireframe = !isWireframe;
  }

  if (key == GLFW_KEY_W && action == GLFW_RELEASE && wPressedDown) {
    wPressedDown = false;
  }
  if (key == GLFW_KEY_S && action == GLFW_RELEASE && sPressedDown) {
    sPressedDown = false;
  }
}

void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
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
  glfwSetErrorCallback(error_callback);

  Renderer renderer;
  renderer.init();

  // currently in screen space space
  player_rect = {0, 0, 300, 300};

  int width, height;

  while (!glfwWindowShouldClose(window)) {

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    renderer.setScreenDimensions(width, height);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer.drawRect(player_rect);

    if (wPressedDown) {
      player_rect.y += 5;
    }

    if (sPressedDown) {
      player_rect.y -= 5;
    }

    if (isWireframe) {
      renderer.toggleWireframe();
      isWireframe = false;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
