#include "PhysicsSystem.h"
RaycastHandler PhysicsSystem::rch;
b2World* PhysicsSystem::m_world;
float PhysicsSystem::MPP = 40.f;
float PhysicsSystem::Gravity = MPP / -0.5f;

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Init()
{
	m_world = new b2World(b2Vec2(0, Gravity));
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);
}


void PhysicsSystem::UpdateWorld(float dt)
{
	m_world->Step(dt, 6,3);
}

void PhysicsSystem::MakeListener(std::function<void(Entity*,Entity*)> func){
  ContactListener* Listener = new ContactListener();
  Listener->OnContactCallBack = func;
  GetWorld()->SetContactListener(Listener);
}
