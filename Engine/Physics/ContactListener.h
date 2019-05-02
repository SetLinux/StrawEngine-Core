#pragma once
#include <Box2D/Box2D.h>
#include <functional>
#include "../Game/Entity.h"
class ContactListener : public b2ContactListener{
 public:
  virtual void BeginContact(b2Contact* contact);
  virtual void EndContact(b2Contact *contact){};
  std::function<void(Entity* A,Entity* B)> OnContactCallBack;
    
};
