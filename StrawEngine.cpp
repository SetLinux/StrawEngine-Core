#include "Engine/Addons/Animator.h"
#include "Engine/Game/Entity.h"
#include "Engine/Game/Game.h"
#include "Engine/IO/Window.h"
#include "Engine/Rendering/Animation.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
class MyGame : public Game {
  class Clickalbe : public Addon {
  public:
    Game *game;
    std::vector<Entity *> *enems;
    float timer = 0;
    void OnUpdate(float dt, float alpha) override {
      timer += dt;
      if (timer > 20.f) {
        for (std::vector<Entity *>::iterator it = enems->begin();
             it != enems->end(); it++) {
          if (*it == owner) {
            game->DeleteEntitiy(owner);
            (*enems).erase(it);
            break;
          }
        }
      }
    }

    static int GetType() { return 12; };
    int myType() override { return 12; };
  };
  float timer = 0;
  std::vector<EntityHandler> enemies;
  std::random_device dev;
  EntityHandler cursor;
  float deltaX;
  float deltaY;
  int score = 0;
  int counter = 0;
  void Start() override {
    srand(time(0));
    cursor = MakeSprite(X_Vector(0, 0, -1), X_Vector(25, 25), false);
    cursor->GetAddon<Sprite>()->tex =
        GetTexture("/home/mohamedmedhat/Desktop/StrawEngine/build/wall.jpg")
            .get();
  }
  void Update(float dt) override {}
  void FixedUpdate(float dt) override {
    timer += dt;
    if (timer > 0.4f) {
      std::mt19937 rng(dev());
      std::uniform_int_distribution<std::mt19937::result_type> dist6(
          -490, 490); // distribution in range [1, 6]

      int result = dist6(rng);
      EntityHandler Enemy =
          MakeSprite(X_Vector(result, 400), X_Vector(128, 128));
      Enemy->GetAddon<Sprite>()->tex =
          GetTexture("/home/mohamedmedhat/Desktop/StrawEngine/build/minecraft.png")
              .get();
      Enemy->GetAddon<Sprite>()->SetTexBound(16 + 32,0,16,16);
      Enemy->AddAddon<Clickalbe>()->game = this;
      Enemy->GetAddon<Clickalbe>()->enems = &enemies;
      enemies.emplace_back(Enemy);
      timer = 0;
    }
    X_Vector finale = Camera::main.ScreenToWorld(
        X_Vector(m_Window->mousexpos, m_Window->mouseypos));
   
    if (X_Vector::Distance(cursor->position, finale) > 0.1f) {
      PhysicsSystem::RayCast(cursor->position, finale, [&](Entity *A) {
        for (int i = 0; i < enemies.size(); i++) {
          if (enemies[i]) {
            if (enemies[i] == A) {
              DeleteEntitiy(enemies[i]);
	      score += 1;
	      enemies[i] = nullptr;
            }
          }
        }
      });
    }
    for (int i = 0; i < enemies.size(); i++) {
      if (enemies[i]) {
        bool found = enemies[i]
                         ->GetAddon<Physics>()
                         ->getBody()
                         ->GetFixtureList()
                         ->TestPoint(X_Vector::ToVec<b2Vec2>(
                             cursor->position / PhysicsSystem::MPP));
        if (found) {
          DeleteEntitiy(enemies[i]);
	  score += 1;
	  enemies[i] = nullptr;
        }
      }
    }
    finale.z = 20;
    cursor->position = finale;
    
  }
};

int main() {
  PhysicsSystem::Gravity = -40;
  Window x(1000, 1000, "TES");
  MyGame gm;
  x.Loop(&gm);
}
