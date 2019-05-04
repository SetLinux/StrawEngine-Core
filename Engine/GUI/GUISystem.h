#pragma once
#include "../Math/Math.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "../Rendering/Texture.h"
#include <functional>
#include <vector>
#include "../Utils/SNuklear.h"

class Game;

class GUI {
public:
  GUI();
  ~GUI();
  static void Init(Game *game, const std::string &ResPath);
  static void UpdateGUIIO();
  static void BeginRender(float dt);
  static void EndRender();
  static void SetFunction(std::function<void()> input) { myDraw = input; }
  static void LoadScheme(const std::string& schemeFile);
  static void SetFont(const std::string& fontFile);
  static bool Button(X_Vector pos,X_Vector scale,const std::string& text);
  static void Label(const std::string& text);
private:
  static struct  nk_font *roboto;
  static std::function<void()> myDraw;
  static Game *gm;
  static nk_context* ctx;
  static nk_colorf bg;
};
