#include "renderer.hpp"
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

void Shader::initFromFile(const std::string fragmentPath,
                          const std::string vertexPath) {
  std::string vertexSource;
  std::string fragmentSource;

  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.open(vertexPath);
  fShaderFile.open(fragmentPath);

  std::stringstream vShaderS, fShaderS;

  vShaderS << vShaderFile.rdbuf();
  fShaderS << fShaderFile.rdbuf();

  vShaderFile.close();
  fShaderFile.close();

  vertexSource = vShaderS.str();
  fragmentSource = fShaderS.str();

  init(fragmentSource.c_str(), vertexSource.c_str());
}

void Shader::init(const char *fragmentSource, const char *vertexSource) {
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  std::cout << fragmentSource;

  glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
  glShaderSource(vertexShader, 1, &vertexSource, nullptr);

  shaderId = glCreateProgram();
  glAttachShader(shaderId, vertexShader);
  glAttachShader(shaderId, fragmentShader);

  glLinkProgram(shaderId);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
}
