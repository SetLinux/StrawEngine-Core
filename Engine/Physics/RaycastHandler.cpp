#include "RaycastHandler.h"



RaycastHandler::RaycastHandler()
{
}


RaycastHandler::~RaycastHandler()
{
}
//Just a normal Box2D CallBack
float32 RaycastHandler::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	Entity* x = (Entity*)fixture->GetBody()->GetUserData();	
	CallBack(x,X_Vector::fromVec(normal));
	return 0;
}
