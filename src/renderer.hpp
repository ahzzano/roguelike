#include <string>
extern const char *vertexShader;
extern const char *fragmentShaderSource;

struct Rect {
  float x;
  float y;
  float w;
  float h;
};

typedef struct Rect Rect;

class Sprite {
  unsigned int textureId;

public:
  std::string file;
  unsigned int id() { return textureId; }
  void load(const std::string filename);
};

class Shader {
private:
  unsigned int shaderId;

public:
  void init(const char *fragmentSource, const char *vertexSource);
  void initFromFile(const std::string fragmentPath,
                    const std::string vertexPath);
  unsigned int id() { return shaderId; }

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
};

class Renderer {
  unsigned int shaderProgram;
  unsigned int buffer;
  unsigned int attrib;
  unsigned int elementBuffer;

  unsigned char *textureData;
  unsigned int texture;

  int screenWidth;
  int screenHeight;

  Shader mainShader;

  bool wireframeMode = false;

  void setupRect(Rect &rect);

public:
  void toggleWireframe();

  void setScreenDimensions(int width, int height) {
    screenWidth = width;
    screenHeight = height;
  }

  void init();
  void drawRect(Rect &rect);
  void drawSprite(Rect &rect, Sprite &sprite);
  void loadImage();
};
