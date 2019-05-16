#pragma once
#include "../Game/Addon.h"
#include "../Math/Math.h"
#include <Box2D/Box2D.h>
#include "../Physics/PhysicsSystem.h"
class Physics : public Addon{
public:
  Physics();
  ~Physics();
  AddonBody(AddonType::PhysicsAddon);
  inline X_Vector GetBodyPosition(){
    return X_Vector::fromVec<b2Vec2>(m_body->GetPosition());      
  };
  inline void SetBodyPosition(X_Vector pos){
    m_body->SetTransform(X_Vector::ToVec<b2Vec2>(pos / PhysicsSystem::MPP),0);
  }
  inline void SetVeloctiy(const X_Vector& in){
    m_body->SetLinearVelocity(X_Vector::ToVec<b2Vec2>(in));
  }
  inline X_Vector getVeloctiy() {
    return X_Vector::fromVec(m_body->GetLinearVelocity());
  }
  inline void SetGravity(float scalar) {
    m_body->SetGravityScale(scalar);
  };
  inline float GetGravityScale() {
    return m_body->GetGravityScale();
  }
  
  inline b2Body* getBody(){
    return m_body ;
  };  
  
private:
  X_Vector prevpos;
  b2Body* m_body;
};
