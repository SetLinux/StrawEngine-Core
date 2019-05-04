#include "Physics.h"
#include "../Game/Entity.h"
#include "../Physics/PhysicsSystem.h"
Physics::Physics()
{

}
Physics::~Physics()
{
  PhysicsSystem::GetWorld()->DestroyBody(m_body);
}
void Physics::OnCreate()
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(
		       owner->position.x / PhysicsSystem::MPP,
		       owner->position.y / PhysicsSystem::MPP);
  bodyDef.userData = (void *)owner;
  bodyDef.fixedRotation = true;
  
  m_body = PhysicsSystem::GetWorld()->CreateBody(&bodyDef);
  b2PolygonShape shape;
  shape.SetAsBox(
		 owner->scale.x / 2 / PhysicsSystem::MPP,
		 owner->scale.y / 2 / PhysicsSystem::MPP);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.0f;
  fixtureDef.restitution = 0.0f;
  m_body->CreateFixture(&fixtureDef);
  m_body->GetFixtureList()->SetFriction(0.0f);
}
void Physics::OnUpdate(float dt, float alpha)
{
  
  X_Vector a = X_Vector::Interpolate(prevpos == X_Vector(0,0) ? X_Vector::fromVec<b2Vec2>(m_body->GetPosition()) * PhysicsSystem::MPP : prevpos, X_Vector::fromVec<b2Vec2>(m_body->GetPosition()) * PhysicsSystem::MPP, alpha);
  owner->position = X_Vector(a.x,a.y,owner->position.z);
}
void Physics::OnFixedUpdate(float dt)
{
  prevpos = X_Vector::fromVec<b2Vec2>(m_body->GetPosition()) * PhysicsSystem::MPP;
  owner->Rotation = m_body->GetTransform().q.GetAngle();
}
