#include "ContactListener.h"
#include "PhysicsSystem.h"
#include "../Addons/Physics.h"
void ContactListener::BeginContact(b2Contact *contact) {
  Entity *A = (Entity *)contact->GetFixtureA()->GetBody()->GetUserData();
  Entity *B = (Entity *)contact->GetFixtureB()->GetBody()->GetUserData();
  OnContactCallBack(A, B,contact);
}
