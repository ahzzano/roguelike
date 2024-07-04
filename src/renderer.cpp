#include "renderer.hpp"
#include <glad/glad.h>
#include <iostream>

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n"
    ")\n";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n"
                                   ")\n";

void Renderer::init() {
  unsigned int fragmentShader, vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  std::cout << "Renderer Initialized";

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Renderer::setupRect(Rect &rect) {

  float vertices[] = {
      rect.x - rect.w / 2, rect.y - rect.h / 2, 0.0,
      rect.x + rect.w / 2, rect.y - rect.h / 2, 0.0,
      rect.x + rect.w / 2, rect.y + rect.h / 2, 0.0,
      rect.x - rect.w / 2, rect.y + rect.h / 2, 0.0,
  };

  unsigned int order[] = {0, 1, 3, 1, 2, 3};

  // unsigned int buffer, attrib;
  glGenBuffers(1, &buffer);
  glGenVertexArrays(1, &attrib);
  glGenBuffers(1, &elementBuffer);

  glBindVertexArray(attrib);

  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(order), order, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  if (wireframeMode) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

// Rect is in Screen Space
void Renderer::drawRect(Rect &rect) {
  setupRect(rect);
  glUseProgram(shaderProgram);
  glBindVertexArray(attrib);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
  // glDrawArrays(GL_TRIANGLES, 0, 3);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::toggleWireframe() { wireframeMode = !wireframeMode; }
