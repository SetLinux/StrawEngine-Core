#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact){
  Entity* A = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
  Entity* B = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
 
  OnContactCallBack(A,B);
}
