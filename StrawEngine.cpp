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
void testc(Entity *A, Entity *B, b2Contact *contact) {}
class BulletAddon : public Addon {
public:
  void OnCreate() override{

  };
  void OnUpdate(float dt, float alpha) override {
    X_Vector direction = owner->position - lastpos;
    owner->GetAddon<Physics>()->getBody()->SetTransform(
        owner->GetAddon<Physics>()->getBody()->GetPosition(),
        atan2(-direction.x, direction.y));
  };
  void OnFixedUpdate(float dt) override{};
  static int GetType() { return 12; };
  int myType() override { return 12; };
  X_Vector lastpos{0, 0, 0};
};

class PlayerAddon : public Addon {
private:
  Shader *pshdr;
  unsigned int test;

public:
  PlayerAddon(Shader *shdr) { pshdr = shdr; };
  void OnCreate() override { test = pshdr->getuniformloc("srd"); };
  void OnUpdate(float dt, float alpha) override {
    if (red) {
      pshdr->SetFloatUniform(1, test);
      red = false;
      return;
    } else {
      pshdr->SetFloatUniform(0, test);
    };
  };
  void OnFixedUpdate(float dt) override{};
  static int GetType() { return 13; };
  int myType() override { return 13; };
  bool red = false;
};
class MyGame : public Game {
  EntityHandler me, me2, me3;
  EntityHandler wall1, wall2, wall3, wall4;
  EntityHandler test;
  EntityHandler cursor;
  X_Vector lastpos;
  float timebetween = 0.2f;
  int score = 0;
  float timer = 0.0f;
  ShaderBatch *shdrBatch;
  Shader *csshdr;
  Animation *anim;
  void Start() override {
    anim = new Animation();
    anim->MakeAnimation(0, 11);
    anim->speed = 13;
    wall1 = MakeSprite(X_Vector(0, 450, 0), X_Vector(1000, 50, 0), true);
    wall1->GetAddon<Physics>()->SetGravity(0);
    wall1->GetAddon<Sprite>()->tex = GetTexture(
        "/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/wall.jpg");
    wall2 = MakeSprite(X_Vector(0, -450, 0), X_Vector(1000, 50, 0), true);
    wall2->GetAddon<Physics>()->SetGravity(0);
    wall2->GetAddon<Sprite>()->tex = GetTexture(
        "/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/wall.jpg");

    wall3 = MakeSprite(X_Vector(450, 0, 0), X_Vector(50, 900, 0), true);
    wall3->GetAddon<Physics>()->SetGravity(0);
    wall3->GetAddon<Sprite>()->tex = GetTexture(
        "/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/wall.jpg");
    wall4 = MakeSprite(X_Vector(-450, 0, 0), X_Vector(50, 900, 0), true);
    wall4->GetAddon<Physics>()->SetGravity(0);
    wall4->GetAddon<Sprite>()->tex = GetTexture(
        "/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/wall.jpg");
    wall1->GetAddon<Physics>()->getBody()->SetType(b2BodyType::b2_staticBody);
    wall3->GetAddon<Physics>()->getBody()->SetType(b2BodyType::b2_staticBody);
    wall4->GetAddon<Physics>()->getBody()->SetType(b2BodyType::b2_staticBody);
    wall2->GetAddon<Physics>()->getBody()->SetType(b2BodyType::b2_staticBody);

    csshdr = new Shader("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/"
                        "Engine/Shaders/red.frag",
                        "/home/mohamedmedhat/StrawEngine/StrawEngine-Core/"
                        "Engine/Shaders/red.vert");
    csshdr->Init();
    shdrBatch = MakeShaderBatch(csshdr, SortOrder::BackOrder);

    PhysicsSystem::MakeListener([&](Entity *A, Entity *B, b2Contact *contact) {
				  if (B->HasAddon<BulletAddon>()) {
        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold);

        X_Vector norm = X_Vector::fromVec(worldManifold.normal);

        float middle =
	  2 * (X_Vector::Dot(B->GetAddon<Physics>()->getVeloctiy(), norm));

        X_Vector final =
	  B->GetAddon<Physics>()->getVeloctiy() - (norm * middle);

        B->GetAddon<BulletAddon>()->lastpos =
	  B->GetAddon<Physics>()->GetBodyPosition() * PhysicsSystem::MPP;
	
        if (A == me.get()) {
          score += 1;
          A->GetAddon<PlayerAddon>()->red = true;
          float middle2 =
              2 * (X_Vector::Dot(A->GetAddon<Physics>()->getVeloctiy(), norm));

          X_Vector final2 =
              A->GetAddon<Physics>()->getVeloctiy() - (norm * middle);
          A->GetAddon<Physics>()->SetVeloctiy(final2* -1.f);
        }

        B->GetAddon<Physics>()->SetVeloctiy(final.Normalize() * 100);
      }
      if (A->HasAddon<BulletAddon>()) {
        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold);

        X_Vector norm = X_Vector::fromVec(worldManifold.normal);

        float middle =
            2 * (X_Vector::Dot(A->GetAddon<Physics>()->getVeloctiy(), norm));

        X_Vector final =
            A->GetAddon<Physics>()->getVeloctiy() - (norm * middle);

        A->GetAddon<BulletAddon>()->lastpos =
            A->GetAddon<Physics>()->GetBodyPosition() * PhysicsSystem::MPP;

        if (B == me.get()) {
          score += 1;
          B->GetAddon<PlayerAddon>()->red = true;
          A->GetAddon<PlayerAddon>()->red = true;
          float middle2 =
              2 * (X_Vector::Dot(B->GetAddon<Physics>()->getVeloctiy(), norm));

          X_Vector final2 =
              B->GetAddon<Physics>()->getVeloctiy() - (norm * middle);
          B->GetAddon<Physics>()->SetVeloctiy(final2 * -1.f);
        }
        A->GetAddon<Physics>()->SetVeloctiy(final.Normalize() * 100);
      }
    });

    me = MakeSprite(X_Vector(0, 0, 1), X_Vector(100, 100, 20), shdrBatch);
    me->AddAddon<PlayerAddon>(csshdr);
    me3 = MakeSprite(X_Vector(0, 0, 1), X_Vector(100, 770, 20));
    me3->GetAddon<Physics>()->SetGravity(0);
    me3->GetAddon<Physics>()->getBody()->SetType(b2BodyType::b2_staticBody);

    me->GetAddon<Sprite>()->tex = GetTexture(
        "/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/wall.jpg");
    me3->GetAddon<Sprite>()->tex = GetTexture(
        "/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/wall.jpg");

    me->AddAddon<Physics>();
    me->AddAddon<Script>(
        "/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/test.lua");
    test = MakeEntity(X_Vector(0, 0));
    me->GetAddon<Physics>()->getBody()->SetTransform(
        me->GetAddon<Physics>()->getBody()->GetPosition(), Radians(90));
  }
  void Update(float dt) override {
    //    Camera::main.position.x += 1.f;
    timer += dt;

    if (glfwGetKey(m_Window->m_window, GLFW_KEY_SPACE)) {
      if (timer > timebetween) {
        X_Vector direction = (Camera::main.ScreenToWorld(X_Vector(
                                  m_Window->mousexpos, m_Window->mouseypos)) -
                              me->position)
                                 .Normalize();

        EntityHandler bullet = MakeSprite(
            X_Vector(me->position + direction * 100), X_Vector(15, 15, 0));

        bullet->GetAddon<Sprite>()->tex =
            GetTexture("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/"
                       "Assets/laserBallNull.png");
        bullet->AddAddon<BulletAddon>();
        bullet->AddAddon<Animator>();
        bullet->GetAddon<Animator>()->SetSpriteDimension(X_Vector(32, 32));
        bullet->GetAddon<Animator>()->SetAnim(anim);
        bullet->GetAddon<Physics>()->SetGravity(0);
        bullet->GetAddon<Physics>()->getBody()->SetBullet(true);
        bullet->GetAddon<Physics>()->SetVeloctiy(direction * 100.f);
        bullet->GetAddon<Physics>()->getBody()->GetFixtureList()->SetDensity(
            10.f);
        bullet->GetAddon<Physics>()->getBody()->ResetMassData();
        bullet->scale.x += 40;
        bullet->scale.y += 40;
        timer = 0;
      }
    }
  }
  void FixedUpdate(float dt) override {}

  void OnGUI() override {

    GUI::Label("Hits : " + std::to_string(score), 0, 0, 300, 300);
  }
};

int main() {
  PhysicsSystem::Gravity = -40;
  Window x(1000, 1000, "TES");
  MyGame gm;

  x.Loop(&gm);
}
