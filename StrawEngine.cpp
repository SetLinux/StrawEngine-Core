#include "Engine/Addons/Animator.h"
#include "Engine/Addons/Script.h"
#include "Engine/Game/Entity.h"
#include "Engine/Game/Game.h"
#include "Engine/IO/Window.h"
#include "Engine/Rendering/Animation.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
class CustomShader : public Shader {
public:
  CustomShader(std::string fragpath, std::string verpath)
      : Shader(fragpath, verpath) {}
};
class MyGame : public Game {
  EntityHandler me;
  TextureHandler button;
  void Start() override {
    me = MakeSprite(X_Vector(500, 0, 1), X_Vector(100, 100, 20), false);
    me->GetAddon<Sprite>()->tex = GetTexture(
        "/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/wall.jpg");
    me->AddAddon<Script>(
        "/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/test.lua");
    button = GetTexture("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/"
                        "Assets/blueSheet.png");
    button->Init();
    
  }
  void Update(float dt) override {}
  void FixedUpdate(float dt) override {}
  void OnGUI() override {
    GUI::Button("MAN",400,400,200,200);
    
  }
};

int main() {
  PhysicsSystem::Gravity = -40;
  Window x(1000, 1000, "TES");
  MyGame gm;

  x.Loop(&gm);
}
