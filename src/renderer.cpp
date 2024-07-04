#include "renderer.hpp"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stb_image.h>

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n";
void Renderer::init() {
  mainShader.initFromFile("assets/shaders/fragment.glsl",
                          "assets/shaders/vertex.glsl");
  loadImage();
}

void Renderer::loadImage() {

  int width, height, nrChannels;
  textureData = stbi_load("assets/power.png", &width, &height, &nrChannels, 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, textureData);
  glGenerateMipmap(GL_TEXTURE_2D);
}

float t = 0.0;

void Renderer::setupRect(Rect &rect) {
  float halfsize_x = rect.w / 2;
  float halfsize_y = rect.h / 2;

  float scaleX = 1.0 / screenWidth;
  float scaleY = 1.0 / screenHeight;

  float vertices[] = {(rect.x - halfsize_x) * scaleX,
                      (rect.y - halfsize_y) * scaleY,
                      0.0,
                      0.0f,
                      0.0f,
                      (rect.x + halfsize_x) * scaleX,
                      (rect.y - halfsize_y) * scaleY,
                      0.0,
                      1.0f,
                      0.0f,
                      (rect.x + halfsize_x) * scaleX,
                      (rect.y + halfsize_y) * scaleY,
                      0.0,
                      1.0f,
                      1.0f,
                      (rect.x - halfsize_x) * scaleX,
                      (rect.y + halfsize_y) * scaleY,
                      0.0,
                      0.0f,
                      1.0f};

  unsigned int order[] = {0, 1, 3, 1, 2, 3};

  // unsigned int buffer, attrib;
  glGenBuffers(1, &buffer);
  glGenVertexArrays(1, &attrib);
  glGenBuffers(1, &elementBuffer);

  glBindVertexArray(attrib);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(order), order, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned long long stride = 5 * sizeof(float);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride,
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

// Rect is in Screen Space
void Renderer::drawRect(Rect &rect) {
  setupRect(rect);

  glUseProgram(mainShader.id());

  glBindVertexArray(attrib);
  if (wireframeMode) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  mainShader.setFloat("time", t);
  t += 0.05;
}

void Renderer::drawSprite(Rect &rect, Sprite &sprite) {
  setupRect(rect);
  glUseProgram(mainShader.id());

  glBindVertexArray(attrib);
}

void Renderer::toggleWireframe() { wireframeMode = !wireframeMode; }
