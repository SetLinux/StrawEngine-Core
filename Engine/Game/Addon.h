#pragma once
#include <memory>
#define AddonBody(X)							\
  void OnCreate() override;                                                    \
  void OnUpdate(float dt, float alpha) override;                               \
  void OnFixedUpdate(float dt) override;                                       \
  static int  GetType() { return X; };                                    \
  int myType() override { return X; };

#define AddonBodyHeaderOnly(X)							\
  void OnCreate() override{};                                                  \
  void OnUpdate(float dt, float alpha) override{};                             \
  void OnFixedUpdate(float dt) override{};                                     \
  static int GetType() { return X; };                                          \
  int myType() override { return X; };

class Entity;
enum AddonType {
  None,
  SpriteAddon ,
  AnimationAddon,
  PhysicsAddon,
  ScriptAddon
};
class Addon {
public:
  virtual ~Addon(){};
  virtual void OnCreate();
  virtual void OnUpdate(float dt, float alpha);
  virtual void OnFixedUpdate(float dt);
  virtual int myType() { return AddonType::None; };
  // virtual AddonType GetType(){return AddonType::None;};
  std::shared_ptr<Entity> owner;  
};
