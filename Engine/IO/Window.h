#pragma once
#include <GL/glew.h>
#include <string>
#include "../Utils/nuklear.h"
#include "../Utils/nuklear_sdl_gl3.h"
#include <GLFW/glfw3.h>
class Game;
class Window {
public:
  Window(int width, int height, std::string Title);
  ~Window();
  void Loop(Game *);
  GLFWwindow *m_window;
  static int S_HEIGHT, S_WIDTH;
  Uint8 *state;
  
  double mousexpos,mouseypos;
  nk_context* ctx;
private:
  static int m_width, m_height;
  static std::string m_title;
};
