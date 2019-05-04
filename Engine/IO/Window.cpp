#include "Window.h"
#include "../GUI/imgui.h"
#include "../GUI/imgui_impl_opengl3.h"
#include "../GUI/imgui_impl_sdl.h"
#include "../Game/Game.h"
#include <iostream>
#include <thread>
int Window::m_width, Window::m_height;
std::string Window::m_title;
int Window::S_WIDTH = 1000;
int Window::S_HEIGHT = 1000;
Window::Window(int width, int height, std::string Title) {
  glfwInit();
  m_width = width;
  m_height = height;
  S_WIDTH = width;
  S_HEIGHT = height;
  m_title = Title;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  m_window = glfwCreateWindow(width, height,Title.c_str(), NULL, NULL);
  glfwMakeContextCurrent(m_window);
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cout << "Couldn't Initialize GLEW" << std::endl;
  }
  glViewport(0, 0, width, height);
  const GLubyte *vendor = glGetString(GL_VENDOR); // Returns the vendor
  std::cout << "GL Vendor : " << vendor << std::endl;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  // SDL_SetRelativeMouseMode(SDL_TRUE);
  //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
  glfwSwapInterval(1);
}
Window::~Window() {}
void Window::Loop(Game *game) {
  game->m_Window = this;
  game->InnerInit();
  float t = 0.0;
  float dt = 1.0f / 59.9661f;
  // float dt =1.f/ 60.01f;
  float currentTime = glfwGetTime();
  float accumulator = 0.0;

  float lastTime = glfwGetTime(), timer = lastTime;
  float deltaTime = 0, nowTime = 0;
  int frames = 0, updates = 0;

  bool Open = true;
  while (!glfwWindowShouldClose(m_window)) {
    glfwPollEvents();
    glfwGetCursorPos(m_window,&mousexpos,&mouseypos);
    GUI::UpdateGUIIO();
    int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
    nowTime = glfwGetTime();
    deltaTime += (nowTime - lastTime);
    lastTime = nowTime;
    float newTime = glfwGetTime();
    float frameTime = newTime - currentTime;
    if (frameTime > 0.25)
      frameTime = 0.25;
    currentTime = newTime;
    accumulator += frameTime;
    while (accumulator >= dt) {
    game->InnerFixedUpdate(dt);
    t += dt;
    accumulator -= dt;
     
    const float alpha = accumulator / dt;
    game->InnerUpdate(deltaTime, alpha);
    glfwSwapBuffers(m_window);
    deltaTime = 0;
     
    }
  }
}
