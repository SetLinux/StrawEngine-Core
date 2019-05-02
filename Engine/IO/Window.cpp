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
void test() {
  /*
          PhysicsSystem::UpdateWorld(1.f / 60.f);
          PhysicsSystem::UpdateTransformOn(sprite);
          PhysicsSystem::UpdateTransformOn(sprite2);

          glClear(GL_COLOR_BUFFER_BIT);
          glClearColor(1, 0, 0, 1);
          glEnable(GL_MULTISAMPLE);
          sprite->position.x += 0.01f;
          sprite->ApplyTransformation();


          renderer.Begin();

          renderer.Submit(sprite);
          renderer.Submit(sprite2);
          renderer.End();
          glfwSwapBuffers(m_window);
          glfwPollEvents();
          glfwSwapInterval(1);
  */
}
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
  std::cout << vendor << std::endl;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  // SDL_SetRelativeMouseMode(SDL_TRUE);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glfwSwapInterval(1);
  glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
}

Window::~Window() {}

void Window::Loop(Game *game) {
  game->m_Window = this;
  game->InnerInit();
  float t = 0.0;
  float dt = 1.0f / 60.f;
  // float dt =1.f/ 60.01f;
  float currentTime = glfwGetTime();
  float accumulator = 0.0;

  float lastTime = glfwGetTime(), timer = lastTime;
  float deltaTime = 0, nowTime = 0;
  int frames = 0, updates = 0;

  bool Open = true;
  while (!glfwWindowShouldClose(m_window)) {
    glfwPollEvents();
    GUI::UpdateGUIIO(event);
    int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
      {
	std::cout << "PRESS" << std::endl;
      }
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
      
    }
      
      const float alpha = accumulator / dt;
      game->InnerUpdate(deltaTime, alpha);
      
      glfwSwapBuffers(m_window);
      deltaTime = 0;

  }
}
