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

class Renderer {
  unsigned int shaderProgram;
  unsigned int buffer;
  unsigned int attrib;
  unsigned int elementBuffer;

  bool wireframeMode = false;

public:
  void toggleWireframe();

  void init();
  void setupRect(Rect &rect);
  void drawRect(Rect &rect);
};
